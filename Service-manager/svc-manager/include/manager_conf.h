#ifndef MANAGER_CONF_H
#define MANAGER_CONF_H

#include <sys/types.h>

void display_services(void);

typedef struct {
  char* name;
  char* cmd;
  pid_t pid;
} service_s;

#endif
