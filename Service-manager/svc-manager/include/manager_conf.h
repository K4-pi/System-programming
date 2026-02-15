#ifndef MANAGER_CONF_H
#define MANAGER_CONF_H

#include <sys/types.h>

typedef struct {
  char* name;
  char* cmd;
  pid_t pid;
} service_s;

void display_services(void);
service_s* get_service_by_name(char* name);

#endif
