#include <complex.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BUFFER_SIZE 512

void TCP_server(int Port)
{
    printf("Initialiazing server...\n");    
    const char* hello = "Packet recived\n";

    int opt = 1;
    char buffer[BUFFER_SIZE] = { 0 };

    // Assigning variables
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    sock_addr.sin_port = htons(Port);
    socklen_t addr_len = sizeof(sock_addr);

    // Sockets
    int commmunication_socket, sockfd;
   
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Faild creating socket");
        exit(1);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if (bind(sockfd, (struct sockaddr*)&sock_addr, addr_len) == -1)
    {
        perror("Bind error!");
        exit(1);
    }
    if (listen(sockfd, 3) == -1) //why 3?
    {
        perror("Listen error!");
        exit(1);
    }
    if ((commmunication_socket = accept(sockfd, (struct sockaddr*)&sock_addr, &addr_len)) == -1)
    {
        perror("Accept error!");
    }
    while (1) 
    {
        read(commmunication_socket, buffer, BUFFER_SIZE * sizeof(char));
        printf("%s\n", buffer);
        send(commmunication_socket, hello, strlen(hello), 0);
        memset(buffer, 0, BUFFER_SIZE - 1); //clearing buffer
    }
    close(commmunication_socket);
    close(sockfd);
}
