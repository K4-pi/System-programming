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
    char **tokens = calloc(buffer_size, sizeof(char));

    if (tokens == NULL) {
        fprintf(stderr, "csh: allocation error! (csh_split_line.c : 17)\n");
    }

    token = strtok(line, CSH_TOK_DELIM);
    

}
