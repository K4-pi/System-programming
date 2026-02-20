# Simple Service Manager

A minimal Linux service manager written in C.  
This project demonstrates low-level UNIX process management, signal handling, and event-driven I/O using epoll.

## Overview

This service manager is capable of:

- Starting services using `fork()` and `execvp()`
- Monitoring child processes
- Handling `SIGCHLD` to detect terminated services
- Reaping zombie processes using `waitpid()`
- Managing socket communication
- Using `epoll()` for scalable event-driven I/O

The goal of this project is to understand how real-world init systems and supervisors work at a fundamental level.

---

## Technologies and System Calls Used

- `fork()` – create child processes
- `execvp()` – execute service commands
- `waitpid()` – reap terminated child processes
- `SIGCHLD` – detect when a child exits
- `signal()` – register signal handlers
- `socket()` – IPC or network communication
- `epoll()` – scalable event loop for handling multiple file descriptors

## Limitations

Unfortunetly services command needs to be contained in one line ending with semicolon so it doesn't support
commands with more than one line.

## Architecture

### 1. Manager launch

- Manager loads services to a table from configuration file 

### 2. Service Launch

- Cli tool sends `start` command
- The manager forks a child process.
- The child replaces itself with a service using `execvp()`.

### 3. Service Stop

- Cli tool sends `stop` command
- The manager sends SIGTERM singal to process
- If process doesn't stop sends SIGKILL signal
- Clears service pid in table

### 4. Process Monitoring

- When a child exits, the kernel sends `SIGCHLD`.
- The signal handler sets a flag.
- The main loop calls `waitpid(..., WNOHANG)` to reap exited services.

### 5. Event Loop

- `epoll()` monitors sockets or file descriptors.
- The manager reacts to incoming events without blocking.

---

## Run

### Manager:
```bash
./manager
```
Starts manager

### Cli:
```bash
./cli start <service-name>
```
Starts service if it exists

```bash
./cli stop <service-name>
```
Stops service if it exists and is running

```bash
./cli status <service-name>
```
Sends reqest for service informations and displays them

## Purpose

This project is educational and focuses on:
- Understanding Linux process lifecycle
- Learning signal handling
- Building a basic supervisor from scratch
- Practicing event-driven programming in C
- How SIGCHLD works
- Handling zombie processes
- Use of epoll()
