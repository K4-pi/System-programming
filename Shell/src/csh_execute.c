#include "csh_execute.h"
#include "csh_run_process.h"
#include <stdio.h>
#include <string.h>

int csh_help(char **args);
int csh_exit(char **args);
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
        if (!strcmp(args[0], builtins_str[i])) {
            return (builtins_func[i])(args);
        }
    }
    return csh_run_process(args);
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
    return 1;
}