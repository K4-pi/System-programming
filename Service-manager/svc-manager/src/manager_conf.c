#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "manager_conf.h"
#include "manager_string.h"

static char* read_conf_file(void);
static service_s* get_services_conf(char* buffer, size_t* num_services);

static char* read_conf_file(void) {
  FILE* conf_file = fopen("conf/services.conf", "rb");
  if (conf_file == NULL) {
    perror("SVC manager: failed to open .conf file\n");
    return NULL;
  }

  size_t BUFFER_SIZE = 32;
  size_t index = 0;  

  char c;
  char* buffer = calloc(BUFFER_SIZE, sizeof(char));
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

static service_s* get_services_conf(char* buffer, size_t* num_services __attribute__((unused))) {
  size_t count = 0;
  size_t BUFFER_SIZE = 32;
  service_s* services = calloc(BUFFER_SIZE, sizeof(service_s));
  
  char** services_token = parse_str(buffer, ",");
  char** service_token;

  while (services_token[count]) {
    if (count >= BUFFER_SIZE) {
      BUFFER_SIZE *= 2;
      service_s* tmp_buffer = realloc(services, BUFFER_SIZE * sizeof(service_s));

      if (!tmp_buffer) {
        perror("SVC manager: realloc error\n");
        free(tmp_buffer);
        return NULL;
      }

      services = tmp_buffer;
    }
    service_token = parse_str(services_token[count], "{};");

    services[count].name = strtok(service_token[0], " ");
    size_t i = 1;
    while (service_token[i]) {
      char** tmp_tok = parse_str(service_token[i], "=");
      if (strcmp(tmp_tok[0], "cmd") == 0) services[count].cmd = tmp_tok[1];
      free(tmp_tok);
      i++;
    }
    
    free(service_token);
    count++;
  }
  *num_services = count;
  
  free(services_token);
  return services;
}

service_s* get_service_by_name(char* name) {
  char* conf_buffer = read_conf_file();
  if (!conf_buffer) {
    free(conf_buffer);
    return NULL;
  }

  size_t services_num;
  service_s* services = get_services_conf(conf_buffer, &services_num);
  if (!services) {
    free(services);
    return NULL;
  }
  
  for (size_t i = 0; i < services_num; i++) {
    printf("Given name:%s\n", name);
    printf("Found name:%s\n", services[i].name);

    if (strcmp(services[i].name, name) == 0) {
      return &services[i];
    }
  }

  free(services);
  free(conf_buffer);
  printf("SVC info: service called %s not found\n", name);
  return NULL;
}

void display_services(void) {
  char* s = read_conf_file();
  if (s) printf("Config file: \n%s\n", s);
  else printf("Something went wrong with config file?\n");

  size_t services_num;
  service_s* services = get_services_conf(s, &services_num);

  for (size_t i = 0; i < services_num; i++) {
    printf("\nNumber of services: %lu\n", services_num);
    printf("name: %s\n", services[i].name);
    printf("cmd: %s\n", services[i].cmd);
    printf("pid: %d\n", services[i].pid);
  }
}
