#include "simple_shell.h"

/**
 * disable_input_buffering - Disables input buffering and echo.
 */
void disable_input_buffering(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * enable_input_buffering - Enables input buffering and echo.
 */
void enable_input_buffering(void)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ICANON | ECHO;
	tcsetattr(STDERR_FILENO, TCSANOW, &term);
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("#cisfun$ ");
	fflush(stdout);
}

/**
 * read_input - Reads user input.
 * @buffer: Buffer to store the input.
 * Return: Number of characters read.
 * @size: Size of the buffer.
 */
int read_input(char *buffer, __attribute__((unused))size_t size)
{
	int c;
	size_t i = 0;
	

	while ((c = getchar()) != '\n' && c != EOF)
	{
		if (c == 27)
		{
			getchar();
			switch (getchar())
			{
				case 'A':

					break;
				case 'B':

					break;
				case 'C':
					putchar(27);
					putchar('[');
					putchar('C');
					break;
				case 'D':
					putchar(27);
					putchar('[');
					putchar('D');
					break;
			}
		}
		else
		{
			buffer[i++] = c;
			putchar(c);
		}
	}

	buffer[i] = '\0';
	return (i);
}


/**
 * main - Entry point for the simple shell.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{

	char input_buffer[MAX_INPUT_SIZE];
	(void)argc;
	(void)argv;

	disable_input_buffering();

	if (isatty(fileno(stdin)))
	{
		while (1)
		{
			display_prompt();
			if (read_input(input_buffer, sizeof(input_buffer)) == 0)
				break;


			input_buffer[strcspn(input_buffer, "\n")] = '\0';
			execute_command(input_buffer);
		}
	}
	else
	{
		while (read_input(input_buffer, sizeof(input_buffer)) != 0)
		{
			input_buffer[strcspn(input_buffer, "\n")] = '\0';
			run_command(input_buffer);
		}
	}

	enable_input_buffering();

	return (0);
}
