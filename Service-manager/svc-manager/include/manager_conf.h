#ifndef MANAGER_CONF_H
#define MANAGER_CONF_H

#include <sys/types.h>

typedef enum {
  FALSE,
  TRUE
} BOOL;

typedef struct {
  char* name;
  char* cmd;
  BOOL enabled;
  pid_t pid;
} service_s;


void display_services(service_s* services, size_t services_num); 
char* read_conf_file(void);
service_s* get_service_by_name(service_s* services, size_t services_num, char* name);
service_s* get_services_conf(char* buffer, size_t* num_services);
service_s* get_service_by_pid(service_s* services, size_t services_num, pid_t pid); 

#endif
