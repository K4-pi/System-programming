CC = gcc
CFLAGS = -Wall -Wextra

MANAGER_SRC := $(wildcard svc-manager/src/*.c)
MANAGER_INCLUDE := -Isvc-manager/include

CLI_SRC := $(wildcard svc-cli/src/*.c)
CLI_INCLUDE := -Isvc-cli/include

all: manager cli

manager:
	$(CC) $(CFLAGS) -o manager svc-manager/svc-manager.c $(MANAGER_SRC) $(MANAGER_INCLUDE) 

cli:
	$(CC) $(CFLAGS) -o cli svc-cli/svc-cli.c $(CLI_SRC) $(CLI_INCLUDE)

clean:
	rm -f cli manager
