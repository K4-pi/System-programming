#ifndef MANAGER_COMMANDS_H
#define MANAGER_COMMANDS_H

typedef void (*function)(void);

typedef struct {
    char* name;
    function fn;
} cmd;

extern cmd cmds[];

#endif
