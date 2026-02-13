#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager_string.h"

char** parse_str(char* str, char* delim) {
  int BUFFER_SIZE = 64;
  int index = 0;
  char* tok = strtok(str, delim);
  char** buffer = calloc(BUFFER_SIZE, sizeof(char*));
  
  while (tok != NULL) {
    if (index >= BUFFER_SIZE - 1) {
      BUFFER_SIZE *= 2;
      char** tmp_buffer = realloc(buffer, BUFFER_SIZE * sizeof(char*));
      if (!tmp_buffer) {
        perror("SVC manager: commands realloc error\n");
        free(buffer);
        return NULL;
      }
      buffer = tmp_buffer;
    }
    
    buffer[index] = tok;
    index++;
    tok = strtok(NULL, delim);
  }

  return buffer;
}
