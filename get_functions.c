#include <stdio.h>
#include "myshell.h"
#include <stdlib.h>
#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    char input_buffer[MAX_INPUT_SIZE];
    while (1)
    {
        display_prompt();
        if (read_input(input_buffer) == 0)
            break;
        
        
        input_buffer[strcspn(input_buffer, "\n")] = '\0';
        if (strcmp(input_buffer, "exit") == 0)
        break;
        execute_command(input_buffer);
    }
    return (0);
}

void display_prompt(void)
{
    printf("myshell>");
}

int read_input(char *buffer)
{
    if (fgets(buffer, MAX_INPUT_SIZE, stdin) == NULL)
    {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }
    return strlen(buffer);
}

void execute_command(char *command)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        execlp(command, command, (char *)NULL);
        perror("exec");

    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            printf("Child process exited with status %d\n", WEXITSTATUS(status));

        else
            printf("Child process did not exit normally\n");
    }
}