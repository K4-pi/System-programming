#include <stdlib.h>

#include "stdio.h"
#include "csh.h"
#include "csh_read_line.h"
#include "csh_split_line.h"
#include "csh_execute.h"

int lsh_execute(char **args);

void csh_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        
        line = csh_read_line();
        args = csh_split_line(line);
        
        status = csh_execute(args);

        free(line);
        free(args);
    } while (status);    
}


