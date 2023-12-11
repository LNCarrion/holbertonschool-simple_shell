#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_INPUT_SIZE 1024

void display_prompt();
int read_input(char *buffer);
void execute_command(char *command);

#endif /* MYSHELL_H */