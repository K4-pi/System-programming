#include "csh_run_process.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int csh_run_process(char **args) {
    pid_t pid, wpid;
    int status;
    
    pid = fork();
    if (pid == 0) {
        //Child
        execvp(args[0], args);
    }
    else if (pid > 0) {
        //Parent
        do {
            wpid = waitpid(wpid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else {
        perror("csh: error while running process!\n");
    }
    return 1;
}
