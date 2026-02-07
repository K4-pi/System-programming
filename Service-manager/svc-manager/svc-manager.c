#include <stdio.h>

#include "manager_socket.h"

int main(void) {
  printf("Hello from manager!\n");

  manager_epoll();

  return 0;
}
