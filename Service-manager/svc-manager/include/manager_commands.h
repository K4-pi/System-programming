#ifndef MANAGER_COMMANDS_H
#define MANAGER_COMMANDS_H

void execute_cmd(char** commands, int client);

void services_init(void);
void services_clean(void); 
void sigchld_handler(int sig);
void clean_unused_processes();

#endif
