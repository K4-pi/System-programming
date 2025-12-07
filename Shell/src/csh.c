#include <stdlib.h>

#include "stdio.h"
#include "csh.h"
#include "csh_read_line.h"
#include "csh_split_line.h"

void csh_loop(void) {
    char *line;
    char **args;
    int status = 1;

    do {
        printf("> ");

        line = csh_read_line();
        printf("line: %s\n", line);

        args = csh_split_line(line);

        for (int i = 0; args[i] != NULL; i++) {
            printf("args[%d]: %s\n", i, args[i]);
        }

        free(line);
        free(args);
    } while (status);
    
}
