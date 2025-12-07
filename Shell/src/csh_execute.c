#include "csh_execute.h"
#include "csh_run_process.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int csh_help(char **args);
int csh_exit(char **);
int csh_cd(char **args);

char *builtins_str[] = {
    "help",
    "exit",
    "cd"
};

int (*builtins_func[])(char **) = {
    &csh_help,
    &csh_exit,
    &csh_cd
};

int csh_builtins_num() {
    return sizeof(builtins_func)/sizeof(char *);
}

int csh_execute(char **args) {
    if (args[0] == NULL) return 1;
    
    for (int i = 0; i < csh_builtins_num(); i++) {
        if (strcmp(args[0], builtins_str[i]) == 0) {
            return (builtins_func[i])(args);
        }
    }
    return csh_run_process(args);
}

char *csh_get_working_directory() {
    long size = pathconf(".", _PC_PATH_MAX);
    if (size == -1) {
        fprintf(stderr, "csh: failed to find _PC_PATH_MAX\n%s\n", strerror(errno));
        size = 64;
    }
    
    char* buf = calloc(size, sizeof(char));
    if (buf == NULL) {
        fprintf(stderr, "csh: allocation error!\n%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (getcwd(buf, size) == NULL) {
        fprintf(stderr, "csh: allocation error!\n%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return buf;
}

int csh_exit(char **args) {
    return 0;
}

int csh_help(char **args) {
    printf("Simple shell written in C :)\n");
    printf("Number of builtin commands: %d \n", csh_builtins_num());
    printf("Builtin commands:\n");
    for (int i = 0; i < csh_builtins_num(); i++)
        printf("[%d] %s\n", i, builtins_str[i]);
    return 1;
}

int csh_cd(char **args) {
    if (chdir(args[1]) == -1) {
        fprintf(stderr, "csh: error changing directory!\n%s\n", strerror(errno));
    }

    return 1;
}