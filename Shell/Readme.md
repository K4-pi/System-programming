# Mini Shell

Simple UNIX-like shell written in C.

## Features
- command execution
- pipes (|)
- multiple piped commands
- basic error handling

## To-do
- redirecting ( <, >)
- lack of error handling in some functions
- multiple pipes ( ls | grep txt | wc -l )

## Why this project?
This project was created to understand how UNIX shells work internally:
process creation, file descriptors, and inter-process communication.

## Technologies
- C (POSIX)
- fork, exec, pipe, dup2

