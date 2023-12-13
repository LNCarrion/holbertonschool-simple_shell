#include "myshell.h"
#include "get_function.c"

/**
check_path - checks if path with command exists
*
* @str: string to add to path
* Return: the path if valid, NULL otherwise
*/
char *check_path(char *str)
{
	char **pathlist = NULL;
	char *full_cmd = NULL;
	int i;

	pathlist = build_path(_getenv("PATH"));

	for (i = 0; pathlist[i]; i++)
	{
		full_cmd = _strcat_dir(pathlist[i], str);
		if (access(full_cmd, F_OK))
			free(full_cmd);
		else
			break;
	}
	if (!pathlist[i])
	{
		free_double(pathlist);
		return (str);
	}
	if (pathlist)
		free_double(pathlist);
	return (full_cmd);
}

/**
*main - runs the shell
*
* @argc: number of arguments
* @argv: array of arguments (strings)
* Return: 0
*/
int main(int argc, char *const argc[])
{
	char **arglist = NULL;
	char *full_cmd = NULL;
	pid_t my_pid;
	int status = 0, isinteractive = 0;
	char ret_code = -1;
	(void)argv;

	isinteractive = isatty(STDIN_FILENO);
	while (argc)
	{
		arglist = arg_list(isinteractive);
		ret_code = builtin_finder(arglist);

		if (ret_code >= 0)
			exit(ret_code);
		my_pid = fork();
		if (my_pid == -1)
		{
			error_call(0, "fork failed", arglist);
			return (1);
		}
		if (my_pid == 0 && ret_code == -1 && arglist)
		{
			if (*arglist[NON_BUILTIN] != '/')
			{
				full_cmd = check_path(arglist[NON_BUILTIN]);
				if (full_cmd && execve(full_cmd, arglist, NULL) == -1)
					error_call(0, full_cmd, arglist);
			}
			else if (execve(arglist[NON_BUILTIN], arglist, NULL) == -1)
			{
				error_call(0, "not found", arglist);
			}
		}
		if (wait(&status) == -1) /* if child failed */
			_exit(status);
		if (arglist && ret_code == -1)
			free_double(arglist);
	}
	return (0);
}

/**
* arg_list - obtains an argument list from the getline
*
* @isinteractive: a flag to indicate interactive mode
* Return: an array of strings that contain the arguments
*/
char **arg_list(int isinteractive)
{
	char **arglist;
	char *buf = NULL;
	int i;
	size_t size_b = 0;

	if (isinteractive)
		print_str("#cisfun$ ");

	i = getline(&buf, &size_b, stdin);
	if (i == -1)
	{
		if (isinteractive)
			write(STDOUT_FILENO, "\n", 1);
		free(buff);
		return (arglist = strtow("exit", ' '));
	}
	*(buf + i - 1) = '\0';

	arglist = strtow(buf, ' ');
	i = 0;

	free(buf);

	return (arglist);
}

/**
* error_call - function for freeing and returning an error
*
* @n: integer in case of specific exit number
* @err: string to print out for error
* @arglist: the arguments to free in case of exits
* Return: n on success
*/
{
	perror(err);
	free_double(arglist);
	return (n);
}






