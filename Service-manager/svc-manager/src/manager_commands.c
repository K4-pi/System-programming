#include <bits/types/idtype_t.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "manager_commands.h"
#include "manager_conf.h"
#include "manager_string.h"

static void start_fn(char* name);
static void stop_fn(char* name);

cmd cmds[] = {
  {"start", start_fn},
  {"stop", stop_fn}
};

size_t cmds_len = sizeof(cmds)/sizeof(cmds[0]);

void execute_cmd(char** commands) {
  printf("\n=========================\n");
  printf("Command: %s\n", commands[0]);
  printf("Argument: %s\n", commands[1]);

  for (size_t i = 0; i < cmds_len; i++) {
    if (strcmp(commands[0], cmds[i].name) == 0) {
      cmds[i].fn(commands[1]);
      break;
    }
  }
}

static void start_fn(char* name) {
  printf("START FUNCTION ON %s!\n", name);

  service_s* s = get_service_by_name(name);
  if (!s) {
    fprintf(stderr, "Error while launching serivce cmd, is NULL\n");
    return;
  }

  printf("CMD: %s\n", s->cmd);

  char* cmd_copy = strdup(s->cmd);
  char** cmd = parse_str(cmd_copy, " ");
  if (!cmd) {
    free(cmd);
    free(cmd_copy);
    fprintf(stderr, "Parse CMD error\n");
    return;
  }

  pid_t pid = fork();
  if (pid == 0) {
    execvp(cmd[0], cmd);
    perror("Execvp error\n");
    _exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    s->pid = pid;
    printf("Created proces %s with PID: %d\n", s->name, pid);
  }

  display_services(); // for debugging

  free(cmd);
  free(cmd_copy);
  printf("START FUNCTION ENDED\n");
}

static void stop_fn(char* name) {
  printf("STOP FUNCTION ON %s!\n", name);
}

