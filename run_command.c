#include "simple_shell.h"

/**
 * run_command - Run a command in non-interactive mode.
 * @command: The command to be executed.
 */
void run_command(char *command)
{
	execute_command(command);
}