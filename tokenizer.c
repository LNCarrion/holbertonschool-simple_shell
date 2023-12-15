#include "simple_shell.h"

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

void free_token_list(TokenList *tokens)
{
    size_t i;

    for (i = 0; i < tokens->size; i++)
    {
        free(tokens->tokens[i]);
    }
    free(tokens->tokens);
}