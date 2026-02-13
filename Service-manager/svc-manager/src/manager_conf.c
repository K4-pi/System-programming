#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "manager_conf.h"
#include "manager_string.h"

static char* read_conf_file(void);
static service_s* get_services_conf(char* buffer);
void display_services(void);

static char* read_conf_file(void) {
  FILE* conf_file = fopen("conf/services.conf", "rb");
  if (conf_file == NULL) {
    perror("SVC manager: failed to open .conf file\n");
    return NULL;
  }

  size_t BUFFER_SIZE = 32;
  size_t index = 0;  
  
  char c;
  char* buffer = calloc(BUFFER_SIZE, sizeof(char*));
  if (!buffer) {
    perror("SVC manager: calloc error\n");
    return NULL;
  }

  while ((c = getc(conf_file)) != EOF) {
    if (index >= BUFFER_SIZE - 1) {
      BUFFER_SIZE *= 2;
      char* tmp_buffer = realloc(buffer, BUFFER_SIZE);

      if (!tmp_buffer) {
        free(tmp_buffer);
        free(buffer);
        perror("SVC manager: conf file realloc error\n");
        return NULL;
      }

      buffer = tmp_buffer;
    }
    if (c != '\n' && c != '\t' && c != '\r') {
      buffer[index] = c;
      index++;
    }
  }

  fclose(conf_file);
  buffer[index] = '\0';
  return buffer;
}

static service_s* get_services_conf(char* buffer) {
  size_t index = 0;
  size_t BUFFER_SIZE = 8;
  service_s* services = calloc(BUFFER_SIZE, sizeof(service_s*));
  
  char** services_token = parse_str(buffer, ",");
  char** service_token;

  while (services_token[index]) {
    if (index >= BUFFER_SIZE) {
      BUFFER_SIZE *= 2;
      service_s* tmp_buffer = realloc(services, BUFFER_SIZE);

      if (!tmp_buffer) {
        perror("SVC manager: realloc error\n");
        free(tmp_buffer);
        return NULL;
      }

      services = tmp_buffer;
    }
    
    service_token = parse_str(services_token[index], "{};");

    services[index].name = service_token[0];
    size_t i = 1;
    while (service_token[i]) {
      char** tmp_tok = parse_str(service_token[i], "=");
      if (strcmp(tmp_tok[0], "cmd") == 0) services[index].cmd = tmp_tok[1];
      i++;
    }
   
    index++;
  }
  
  return services;
}

void display_services(void) {
  char* s = read_conf_file();
  if (s) printf("Config file: \n%s\n", s);
  else printf("Something went wrong with config file?\n");

  service_s* services = get_services_conf(s);

  size_t i = 0;
  while (services[i].name != NULL) {
    printf("\nname: %s\n", services[i].name);
    printf("cmd: %s\n", services[i].cmd);
    printf("pid: %d\n", services[i].pid);
    i++;
  }
  
  free(s);
}
