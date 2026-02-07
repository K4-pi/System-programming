#include "cli_socket.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc == 1 || argc > 3) {
    printf("Pattern: svc-cli [COMMAND] <SERVICE>\n");
    return 1;
  }
  send_to_manager(argv);

  return 0;
}
