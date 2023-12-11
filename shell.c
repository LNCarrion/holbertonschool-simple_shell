#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "myshell.h"

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