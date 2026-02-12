#ifndef MANAGER_COMMANDS_H
#define MANAGER_COMMANDS_H

#include <stddef.h>

typedef void (*function)(void);

typedef struct {
    char* name;
    function fn;
} cmd;

extern cmd cmds[];
extern size_t cmds_len;
#endif
