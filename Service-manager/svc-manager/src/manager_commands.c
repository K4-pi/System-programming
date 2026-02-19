#include <assert.h>
#include <bits/types/idtype_t.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/wait.h>

#include "manager_commands.h"
#include "manager_conf.h"
#include "manager_string.h"

static void start_fn(char* name);
static void stop_fn(char* name);
static void status_fn(char* name, int client);

size_t services_num;
service_s* services;

static sig_atomic_t child_exited = 0;

void sigchld_handler(int sig __attribute__ ((unused))) {
  child_exited = 1;
}

void clean_unused_processes() {
  if (child_exited) {
    child_exited = 0;

    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
      printf("Service %d exited\n", pid);

      service_s* s = get_service_by_pid(services, services_num, pid);
      if (s) {
        s->pid = 0;
      }
    }
  }
}

void services_init(void) {
  char* conf_buffer = read_conf_file();
  if (!conf_buffer) {
    free(conf_buffer);
    perror("Error reading config file\n");
    return;
  }

  services = get_services_conf(conf_buffer, &services_num);
  if (!services) {
    free(services);
    perror("Error getting services\n");
    return;
  }
}

void services_clean(void) {
  free(services);
}

void execute_cmd(char** commands, int client) {
  printf("\n=========================\n");
  printf("Command: %s\n", commands[0]);
  printf("Argument: %s\n", commands[1]);
  
  if (strcmp(commands[0], "start") == 0) {
    start_fn(commands[1]);
  }
  else if (strcmp(commands[0], "stop") == 0) {
    stop_fn(commands[1]);
  }
  else if (strcmp(commands[0], "status") == 0) {
    status_fn(commands[1], client);  
  }
}

void status_fn(char* name, int client) {
  printf("STATUS FUNCTION ON %s\n", name);
  
  service_s* s = get_service_by_name(services, services_num, name);
  if (!s) {
    fprintf(stderr, "Error while getting service\n");
    return;
  }

  size_t BUFFER_SIZE = snprintf(NULL, 0, "Serivce: %s\nPID: %d\n", s->name, s->pid) + 1;

  char* buffer = calloc(BUFFER_SIZE, sizeof(char));
  snprintf(buffer, BUFFER_SIZE, "Serivce: %s\nPID: %d\n", s->name, s->pid);

  if (send(client, buffer, BUFFER_SIZE, 0) == -1) {
    fprintf(stderr, "error while sending info to client\n");
    free(buffer);
    return;
  }

  free(buffer);
}

static void start_fn(char* name) {
  printf("START FUNCTION ON %s!\n", name);

  service_s* s = get_service_by_name(services, services_num, name);
  if (!s) {
    fprintf(stderr, "Error while getting service\n");
    return;
  }

  printf("CMD: %s\n", s->cmd);

  if (s->pid != 0) {
    printf("Service is already running at PID: %d\n", s->pid);
    return;
  }

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

  display_services(services, services_num); // for debugging

  free(cmd);
  free(cmd_copy);
  printf("START FUNCTION ENDED\n");
}

static void stop_fn(char* name) {
  printf("STOP FUNCTION ON %s!\n", name);

  service_s* s = get_service_by_name(services, services_num, name);
  if (!s) {
    fprintf(stderr, "Error while getting serivce\n");
    return;
  }

  if (s->pid == 0) {
    printf("Can't stop service, is already stopped\n");
    return;
  }

  kill(s->pid, SIGTERM);
  printf("Sending SIGTERM to process\n");

  int status;
  pid_t result = waitpid(s->pid, &status, 0);
  printf("Exit status: %d\n", status);

  if (result <= 0) {
    printf("Sending SIGKILL to process\n");
    kill(s->pid, SIGKILL);
    waitpid(s->pid, &status, 0);
  }
  s->pid = 0;

  if (WIFEXITED(status)) {
    printf("Exited normally = %d\n", WEXITSTATUS(status));
  }
  else if (WIFSIGNALED(status)) {
    printf("Killed by signal = %d\n", WTERMSIG(status));
  }

  printf("STOP FUNCTION ENDED\n");
}

