#include <stdlib.h>

#include "stdio.h"
#include "csh.h"

#define CSH_BUFSIZE_MOD 64

char *csh_read_line(void) {
    int buffer_size = CSH_BUFSIZE_MOD;
    int index = 0;
    int c;

    char *buffer = calloc(buffer_size, sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "csh: allocate error!\n");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[index] = '\0';
            return buffer;
        } 
        else {
            buffer[index] = c;
        }
        index++;

        if (index >= buffer_size) {
            buffer_size += CSH_BUFSIZE_MOD;
            buffer = realloc(buffer, buffer_size);

            if (buffer == NULL) {
                fprintf(stderr, "csh: reallocate error!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void csh_loop(void) {
    char* line;
    int status = 1;

    do {
        printf("> ");

        line = csh_read_line();
        printf("line: %s\n", line);
        free(line);
    } while (status);
    
}
