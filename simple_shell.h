#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define MAX_INPUT_SIZE 1024

typedef struct 
{
    char **tokens;
    size_t size;
} TokenList;

void display_prompt(void);
ssize_t read_input(char **buffer, size_t *size);
TokenList tokenize_input(char *input);
void free_token_list(TokenList *tokens);
void execute_command(TokenList *tokens);
void run_command(char *command);

#endif /* SIMPLE_SHELL_H */