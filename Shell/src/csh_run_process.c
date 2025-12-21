#include "csh_run_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define P_ARGS_MOD 4

int csh_run_process(char **args) {
    int n_pipes = 0;
    int status;
    int P_ARGS_SIZE = P_ARGS_MOD;

    char ***pipe_args = calloc(P_ARGS_SIZE, sizeof(char**));

    pipe_args[0] = &args[0];

    // Finds position of a pipe in args array and slices it
    int index = 0;
    while (args[index] != NULL) {
        if (strcmp(args[index], "|") == 0) {
            pipe_args[n_pipes + 1] = &args[index + 1];
            args[index] = NULL;
            n_pipes++;
        }
        index++;

        // if more than 4 pipes
        if (index + 1 >= P_ARGS_SIZE) {
            P_ARGS_SIZE += P_ARGS_MOD;
            pipe_args = realloc(pipe_args, P_ARGS_SIZE * sizeof(char**));
            if (!pipe_args) {
                perror("Error reallocating");
                free(pipe_args);
                return 0;
            }
        }
    }

    if (n_pipes > 0) {
        int pd[n_pipes + 1][2];
        int n_cmds = n_pipes + 1;

        pid_t pid_arr[n_cmds];

        for (int i = 0; i < n_pipes; i++) 
            pipe(pd[i]);

        for (int i = 0; i < n_cmds; i++) {

            pid_arr[i] = fork();
            if (pid_arr[i] == 0) {
                // stdin
                if (i > 0)
                    dup2(pd[i-1][0], STDIN_FILENO);

                // stdout
                if (i < n_pipes)
                    dup2(pd[i][1], STDOUT_FILENO);

                // closing pipes
                for (int k = 0; k < n_pipes; k++) {
                    close(pd[k][0]);
                    close(pd[k][1]);
                }

                execvp(pipe_args[i][0], pipe_args[i]);
                perror("Pipe exec error");
                _exit(1);
            }
        }

        for (int i = 0; i < n_cmds; i++) {
            close(pd[i][0]);
            close(pd[i][1]);
            waitpid(pid_arr[i], &status, 0);
        }
    }
    else {
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("Exec error");
            _exit(1);
        }

        waitpid(pid, &status, 0);
    }
    return 1;
}
