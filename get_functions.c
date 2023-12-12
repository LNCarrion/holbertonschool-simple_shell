#include <stdio.h>
#include "myshell.h"
#include <stdlib.h>
#include <sched.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void display_prompt(void)
{
    printf("simple_shell> ");
}

int read_input(char *buffer)
{
    if (fgets(buffer, MAX_INPUT_SIZE, stdin) == NULL)
    {
        if (feof(stdin))
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }
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
        fprintf(stderr, "%s: %d: %s: not found\n", __FILE__, __LINE__, command);
        exit(EXIT_FAILURE);

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

void run_command(char *command)
{
    execute_command(command);
}

int main(int argc, char *argv[])
{
    
    char input_buffer[MAX_INPUT_SIZE];
    (void)argc;
    (void)argv;

    if (isatty(fileno(stdin)))
    {
        while (1)
        {
            display_prompt();
            if (read_input(input_buffer) == 0)
                break;
        
        
        input_buffer[strcspn(input_buffer, "\n")] = '\0';
        execute_command(input_buffer);
        }
    }
            else
            {
                while (read_input(input_buffer) != 0)
                {
                    input_buffer[strcspn(input_buffer, "\n")] = '\0';
                    execute_command(input_buffer);
                }
            }
    
    
    return (0);
}