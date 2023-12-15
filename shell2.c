#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void display_prompt() {
	printf("$ ");
	fflush(stdout);
}

void execute_command(char *command) {
	// Check if the command is "exit" or "env" built-in
	if (strcmp(command, "exit") == 0) {
		exit(0);
	} else if (strcmp(command, "env") == 0) {
		char **env = environ;
		while (*env != NULL) {
			printf("%s\n", *env);
			env++;
		}
	} else {
		pid_t pid = fork();

		if (pid == 0) {
			// Child process
			char *args[] = {command, NULL};
			if (execvp(command, args) == -1) {
				perror(command);
				exit(1);
			}
		} else if (pid > 0) {
			// Parent process
			int status;
			waitpid(pid, &status, 0);
			if (WIFEXITED(status)) {
				int exit_code = WEXITSTATUS(status);
				if (exit_code != 0) {
					fprintf(stderr, "%s: exited with status %d\n", command, exit_code);
				}
			}
		} else {
			perror("fork");
		}
	}
}

int main() {
	while (1) {
		display_prompt();

		char input[MAX_INPUT_SIZE];
		if (fgets(input, sizeof(input), stdin) == NULL) {
			// Handle Ctrl+D (EOF)
			printf("\nBye!\n");
			exit(0);
		}

		// Remove the newline character
		input[strcspn(input, "\n")] = '\0';

		// Split the input into command and arguments
		char *command = strtok(input, " ");
		if (command != NULL) {
			// Execute the command
			execute_command(command);
		}
	}

	return 0;
}
