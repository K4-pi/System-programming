#include <stdio.h>

#include "manager_commands.h"

void start_fn(void);
void stop_fn(void);

cmd cmds[] = {
  {"start", start_fn},
  {"stop", stop_fn}
};

void start_fn() {
  printf("START FUNCTION!\n");
}

void stop_fn() {
  printf("STOP FUNCTION!\n");
}

