#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manager_execute.h"
#include "manager_commands.h"

#define DELIM " \n\r\a\t"

char** evaluate_commands(char* str) {
  int BUFFER_SIZE = 64;
  int index = 0;
  char* tok = strtok(str, DELIM);
  char** commands = calloc(BUFFER_SIZE, sizeof(char*));
  
  while (tok != NULL) {
    if (index >= BUFFER_SIZE - 1) {
      BUFFER_SIZE *= 2;
      char** tmp_commands = realloc(commands, BUFFER_SIZE * sizeof(char*));
      if (!tmp_commands) {
        perror("SVC manager: commands realloc error\n");
        free(commands);
        return NULL;
      }
      commands = tmp_commands;
    }
    
    commands[index] = tok;
    index++;
    tok = strtok(NULL, DELIM);
  }

  return commands;
}

int execute_cmd(char** commands) {
  printf("Command: %s\n", commands[0]);
  printf("Argument: %s\n", commands[1]);

  for (int i = 0; i < 2; i++) {
    if (strcmp(commands[0], cmds[i].name) == 0) {
      cmds[i].fn();
      break;
    }
  }

  return 0;
}
