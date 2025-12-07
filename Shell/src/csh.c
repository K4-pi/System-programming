#include <stdlib.h>

#include "stdio.h"
#include "csh.h"



void csh_loop(void) {
    char *line;
    int status = 1;

    do {
        printf("> ");

        line = csh_read_line();
        printf("line: %s\n", line);
        free(line);
    } while (status);
    
}
