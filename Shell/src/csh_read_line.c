#include "csh_read_line.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CSH_BUFSIZE_MOD 64

char *csh_read_line(void) {
    int buffer_size = CSH_BUFSIZE_MOD;
    int index = 0;
    int c;

    char *buffer = calloc(buffer_size, sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "csh: allocation error!\n%s\n", strerror(errno));
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
                fprintf(stderr, "csh: reallocation error!\n%s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
    }
}
