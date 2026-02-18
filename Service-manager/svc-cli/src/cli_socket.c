#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define SOCK_PATH "/tmp/svc.sock"
#define BUFFER_SIZE 64

void send_to_manager(char** argv) {
    int c = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCK_PATH);

    if (connect(c, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("SVC cli: connect error\n");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    memcpy(buffer, argv[1], BUFFER_SIZE);
    strcat(buffer, " ");
    strcat(buffer, argv[2]);

    if (send(c, buffer, sizeof(buffer) - 1, 0) == -1) {
        perror("SVC cli: send error\n");
        close(c);
        exit(EXIT_FAILURE);
    };

    if (strcmp(argv[1], "status") == 0) {
      memset(buffer, 0, BUFFER_SIZE);
      if (recv(c, buffer, 128, 0) == -1) {
        perror("SVC cli: recv error\n");
        close(c);
        exit(EXIT_FAILURE);
      }

      printf("<RECIVED>\n%s", buffer);
        
    }
        
    close(c);
}
