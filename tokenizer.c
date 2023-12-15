#include "simple_shell.h"

/**
 * tokenize_input - Tokenizes the input string.
 * @input: The input string to tokenize.
 * Return: A TokenList containing the tokens.
 */

TokenList tokenize_input(char *input)
{
	char *token;

	static TokenList tokens;

	tokens.size = 0;
	tokens.tokens = NULL;


	token = strtok(input, " \t\n");

	while (token != NULL)
	{
		tokens.size++;
		tokens.tokens = malloc(sizeof(char *) * tokens.size);
		if (tokens.tokens == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		tokens.tokens[tokens.size - 1] = strdup(token);
		token = strtok(NULL, " \t\n");
	}
	return (tokens);
}

/**
 * free_token_list - Frees the memory used by a TokenList.
 * @tokens: Pointer to the TokenList.
 */
void free_token_list(TokenList *tokens)
{
	size_t i;

	for (i = 0; i < tokens->size; i++)
	{
		free(tokens->tokens[i]);
	}
	free(tokens->tokens);
}
