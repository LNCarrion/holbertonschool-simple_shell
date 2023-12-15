#include "simple_shell.h"
#include "shell.h"
/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("simple_shell>");
}

/**
 * read_input - Reads input from stdin.
 * @buffer: Pointer to the buffer to store the input.
 * @size: Pointer to the size of the buffer.
 * Return: Number of bytes read.
 */
ssize_t read_input(char **buffer, size_t *size)
{
	ssize_t bytesRead = getline(buffer, size, stdin);

	if (bytesRead == -1)
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
	return (bytesRead);
}

/**
 * execute_command - Executes a command based on the tokens.
 * @tokens: Pointer to the TokenList.
 */
void execute_command(TokenList *tokens)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);

	}
	else if (pid == 0)
	{
		struct stat file_stat;

		if (stat(tokens->tokens[0], &file_stat) == -1)
		{
			perror("stat");
			_exit(EXIT_FAILURE);
		}

		if (execve(tokens->tokens[0], tokens->tokens, NULL) == -1)
		{
			perror("execve");
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		else
			printf("child process did not exit normally\n");
	}
}

/**
 * run_command - Processes and runs a command.
 * @command: The command to run.
 */
void run_command(char *command)
{
	TokenList tokens = tokenize_input(command);

	execute_command(&tokens);
	free_token_list(&tokens);
}

/**
 * main - Entry point for the simple shell program.
 * Return: Always 0.
 */
int main(void)
{
	char *input_buffer = NULL;
	size_t input_size = 0;
	ssize_t bytesRead;

	while (1)
	{
		display_prompt();
		bytesRead = read_input(&input_buffer, &input_size);

		if (bytesRead == 0)
		{
			break;
		}
		input_buffer[strcspn(input_buffer, "\n")] = '\0';
		run_command(input_buffer);
	}
	free(input_buffer);

	return (0);
}
