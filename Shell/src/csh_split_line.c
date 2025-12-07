#include "csh_split_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSH_BUFSIZE_MOD 64
#define CSH_TOK_DELIM " \t\r\n\a"

char **csh_split_line(char *line) {
    int buffer_size = CSH_BUFSIZE_MOD;
    int index = 0;

    char *token;
    char **buffer = calloc(buffer_size, sizeof(char*));

    if (buffer == NULL) {
        fprintf(stderr, "csh: allocation error! (csh_split_line.c : 17)\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, CSH_TOK_DELIM);
    while (token != NULL) {
        buffer[index] = token;
        index++;

        if (index >= buffer_size) {
            buffer_size += CSH_BUFSIZE_MOD;
            buffer = realloc(buffer, sizeof(char*));

            if (buffer == NULL) {
                fprintf(stderr, "csh: reallocation error! (csh_split_line.c : 31)\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, CSH_TOK_DELIM);
    }
    buffer[index] = NULL;
    return buffer;
}
