#ifndef MANAGER_COMMANDS_H
#define MANAGER_COMMANDS_H

#include <stddef.h>

void execute_cmd(char** commands);

typedef void (*function)(char*);

typedef struct {
    char* name;
    function fn;
} cmd;

void services_init(void);
void services_clean(void); 

#endif
