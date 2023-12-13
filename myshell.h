#ifndef MYSHELL_H
#define MYSHELL_H

#define MAX_INPUT_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define EXIT_BUILTIN 1
#define NON_BUILTIN 0

extern char **environ;

extern int errno;

/**
  * struct built_in - struct for matching commands to built in commands
  * @command: the string matching the command to execute
  * @built_cmd: the built in command to call if command matches
  * Description: Special built in commands for custom shell
  */
typedef struct built_in
{
	char *command;
	char (*built_cmd)(char **, char **);
} do_built;

char *check_path(char *);
char **arg_list(int);
int error_call(int, char *, char **);

/* free */
void free_double(char **);

/* strtow */
char **strtow(char *, char);
int word_counter(char *, char);
char *_malloc(int n, char **);

/* Built in */
char exit_builtin(char **, char **);
char env_builtin(char **, char **);

/* Utility */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat_dir(char *, char *);
int _atoi(char *);

/* Path */
char **build_path(char *);
void print_dir(char *);
void print_env(char **);
char *_getenv(char *);
char *cut_env(char *);

/* prompt */
int print_str(char *);
int builtin_finder(char **);

#endif /*_SHELL_H_*/

void display_prompt(void);
int read_input(char *buffer, size_t size);
void execute_command(char *command);


#endif /* MYSHELL_H */
