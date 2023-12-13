#include "simple_shell.h"

/**
 * execute_command - Executes a shell command.
 * @command: The command to be executed.
 */
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