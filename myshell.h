#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_INPUT_SIZE 1024

void display_prompt(void);
int read_input(char *buffer, size_t size);
void execute_command(char *command);


#endif /* MYSHELL_H */
