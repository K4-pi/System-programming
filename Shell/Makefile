CC = gcc
CFLAGS = -Wall -Wextra -g

SRC_DIR := $(wildcard src/*.c)
INCLUDE_DIR := -Iinclude

all: compile

compile:
	$(CC) $(CFLAGS) main.c -o csh $(SRC_DIR) $(INCLUDE_DIR)

clean:
	rm -f csh
