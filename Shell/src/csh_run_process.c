#include "csh_run_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int csh_run_process(char **args) {
    char ***pipe_args = calloc(8, sizeof(char**));
    int n_pipes = 0;
    int status;

    pipe_args[0] = &args[0];

    // Finds position of a pipe in args array and slices it
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            pipe_args[n_pipes + 1] = &args[i + 1];
            args[i] = NULL;
            n_pipes++;
        }
        i++;
    }

    printf("Pipes: %d\n\n", n_pipes);

    if (n_pipes > 0) {
        int pd[n_pipes + 1][2];

        pid_t pid_arr[n_pipes + 1];

        for (int i = 0; i < n_pipes + 1; i++) {
            pipe(pd[i]);

            pid_arr[i] = fork();
            if (pid_arr[i] == 0) {
                if (i > 0) {
                    dup2(pd[i-1][0], STDIN_FILENO);
                }
                if (i < n_pipes) {
                    dup2(pd[i][1], STDOUT_FILENO);
                }
                for (int k = 0; k < n_pipes + 1; k++) {
                    close(pd[k][0]);
                    close(pd[k][1]);
                }

                execvp(pipe_args[i][0], pipe_args[i]);
                perror("Pipe exec error");
                _exit(1);
            }
        }

        for (int i = 0; i < n_pipes + 1; i++) {
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
    


    // pid_t pid1 = fork();
    // if (pid1 == 0) {
    //     if (pipe_args != NULL) {
    //         dup2(pd[1], STDOUT_FILENO);
    //         close(pd[0]);
    //         close(pd[1]);
    //     }

    //     execvp(args[0], args);
    //     perror("exec error");
    //     _exit(1);
    // }

    // pid_t pid2;
    // if (pipe_args != NULL) {
    //     pid2 = fork();
    //     if (pid2 == 0) {
    //         dup2(pd[0], STDIN_FILENO);
    //         close(pd[0]);
    //         close(pd[1]);
            
    //         execvp(pipe_args[0], pipe_args);
    //         perror("pipe exec error");
    //         _exit(1);
    //     }
    // }

    // close(pd[0]);
    // close(pd[1]);

    // int status;
    // waitpid(pid1, &status, 0);
    // waitpid(pid2, &status, 0);

    return 1;
}
