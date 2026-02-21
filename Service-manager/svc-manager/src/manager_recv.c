#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "manager_recv.h"
#include "manager_commands.h"
#include "manager_string.h"

#define SOCK_PATH "/tmp/svc.sock"
#define DELIM " \n\r\a\t"
#define MAX_EVENTS 64
#define BUFFER_SIZE 64

void manager_loop(void) {
    int s = socket(AF_UNIX, SOCK_STREAM, 0);
    if (s == -1) {
        perror("SVC manager: socket error\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    unlink(SOCK_PATH);

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("SVC manager: bind error");
        exit(EXIT_FAILURE);
    }

    if (listen(s, 5) == -1) {
        perror("SVC manager: listen error\n");
        exit(EXIT_FAILURE);
    }

    printf("listening on %s\n", SOCK_PATH);

    struct epoll_event event, events[MAX_EVENTS];
    int epfd = epoll_create1(0);

    event.events = EPOLLIN | EPOLLET;
    event.data.fd = s;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, s, &event) == -1) {
        perror("SVC manager: epoll add error\n");
    }

    services_init(); //Reads, stores and starts enabled services
    signal(SIGCHLD, sigchld_handler); //When child process changes state

    while (1) {
        int n_ready = epoll_wait(epfd, events, MAX_EVENTS, -1);

        clean_unused_processes();

        for (int i = 0; i < n_ready; i++) {
            if (events[i].data.fd == s) { // NEW connection
                int client;
                if ((client = accept(s, NULL, NULL)) == -1) {
                    perror("SVC manager: accept error");
                }

                event.events = EPOLLIN;
                event.data.fd = client;
                if (epoll_ctl(epfd, EPOLL_CTL_ADD, client, &event) == -1) {
                    perror("SVC manager: epoll add error\n");
                }
            }
            else { // ALREADY connected
                int client_fd = events[i].data.fd;
                char buffer[BUFFER_SIZE];

                while (1) {
                    memset(buffer, 0, BUFFER_SIZE);
                    ssize_t n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
                    
                    if (n > 0) {
                        char** commands = parse_str(buffer, DELIM);
                        if (!commands) {
                            printf("SVC manager: NULL commands\n");
                            free(commands);
                            break;
                        }

                        execute_cmd(commands, client_fd);
                        free(commands);
                    } else if (n == 0) {
                        close(client_fd);
                        break;
                    } else {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        }
                        close(client_fd);
                        break;
                    }
                }
            }
        }
    }
    services_clean(); //Free services data
}

