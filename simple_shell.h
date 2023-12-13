#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#define MAX_INPUT_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termio.h>

void display_prompt(void);
int read_input(char *buffer, size_t size);
void run_command(char *command);
void execute_command(char *command);

#endif /* SIMPLE_SHELL_H */
