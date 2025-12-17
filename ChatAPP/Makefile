all: compile

compile:
	gcc src/mainServer.c -o runserver
	gcc src/client.c -o runclient -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

