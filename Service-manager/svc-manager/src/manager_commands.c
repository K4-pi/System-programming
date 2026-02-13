#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "manager_commands.h"

static void start_fn(void);
static void stop_fn(void);

cmd cmds[] = {
  {"start", start_fn},
  {"stop", stop_fn}
};

size_t cmds_len = sizeof(cmds)/sizeof(cmds[0]);

void execute_cmd(char** commands) {
  printf("Command: %s\n", commands[0]);
  printf("Argument: %s\n", commands[1]);

  for (size_t i = 0; i < cmds_len; i++) {
    if (strcmp(commands[0], cmds[i].name) == 0) {
      cmds[i].fn();
      break;
    }
  }
}

static void start_fn() {
  printf("START FUNCTION!\n");
}

static void stop_fn() {
  printf("STOP FUNCTION!\n");
}

