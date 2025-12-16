#include "csh_run_process.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int pipe_command(char **pargs) {
    pid_t ppid;
    int pstatus;
    ppid = fork();

    if (ppid == 0) {
        // Child
        execvp(pargs[0], pargs);
    } 
    else if (ppid > 0) {
        // Parent
        do {
            waitpid(ppid, &pstatus, WUNTRACED);
        } 
        while (!WIFEXITED(pstatus) && !WIFSIGNALED(pstatus));
    } else {
        perror("csh: error while running pipe process!\n");
    }    
    return 1;
}

int csh_run_process(char **args) {
    pid_t pid;
    int status;
    int pf[2];
    char **pipe_args = NULL;

    // Finds position of a pipe in args array and slices it
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            pipe_args = &args[i + 1];
            args[i] = NULL;
            break;   
        }
        i++;
    }

    // Debug pipe args
    // if (pipe_args != NULL) 
    //     printf("Pipe args: %s\n", pipe_args[0]);

    pipe(pf);
    pid = fork();

    if (pid == 0) {
        // Child
        if (pipe_args != NULL) {
            close(pf[0]);
            dup2(pf[1], STDOUT_FILENO);
            close(pf[1]);
        }

        execvp(args[0], args);
    } 
    else if (pid > 0) {
        // Parent
        do {
            close(pf[1]);
            
            if (pipe_args != NULL) {
                pipe_command(pipe_args);
            }
            
            close(pf[0]);
            waitpid(pid, &status, WUNTRACED);
        } 
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    } else {
        perror("csh: error while running process!\n");
    }
    return 1;
}
