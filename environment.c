#include "shell.h"
/**
 * handle_path - Handles command execution with PATH resolution
 * @args: command and its arguments
 *
 * Return: 0
 */
void handle_path(char **args)
{
	char *path = getenv("PATH");
	char *dir;
	char *command;
	char *f_path;
	int j = 0;

	while (path && path[j])
	{
		dir = extract_directory(path, &j);
		command = construct_command(dir, args[0]);
		f_path = resolve_path(command);

		if (access(f_path, F_OK) == 0)
		{
			args[0] = f_path;
			execute_command(args);
			free(dir);
			free(command);
			free(f_path);
			return;
		}

		free(dir);
		free(command);
		free(f_path);
	}

	handle_errors();
}
/**
 * handle_variables - Function to handle variable replacements
 * @args: command and its arguments
 * @num_args: number of arguments
 * @status: exit status
 *
 * Return: 0
 */
void handle_variables(char **args, int num_args, int status)
{
	int a, b;
	char *arg;
	char *r_arg;
	pid_t pid = getpid();

	for (a = 0; a < num_args; b++)
	{
		arg = args[a];
		r_arg = NULL;

		if (arg[0] == '$')
		{
			if (strcmp(arg, "$$") == 0)
				r_arg = convert_pid_to_string(pid);
			else if (strcmp(arg, "$?") == 0)
				r_arg = convert_exit_status_to_string(get_exit_status(status));
			else
				r_arg = get_environment_variable(arg + 1);
		}

		if (r_arg != NULL)
		{
			free(args[a]);
			args[a] = r_arg;
		}
	}
}
/**
 * handle_exit_status - Handles the $? variable and prints the exit status
 * @status: exit status
 * Return: 0
 */
void handle_exit_status(int status)
{
	int exit_status = get_exit_status(status);

	if (exit_status != -1)
	{
		char *exit_status_str;

		exit_status_str = convert_exit_status_to_string(get_exit_status(status));
		if (exit_status_str != NULL)
		{
			write(STDOUT_FILENO, exit_status_str, strlen(exit_status_str));
			free(exit_status_str);
		}
		else
		{
			write(STDERR_FILENO, "Error: Failed \n", 47);
		}
	}
	else
	{
		write(STDERR_FILENO, "Error: Failed \n", 38);
	}
}
/**
 * get_environment_variable - get environmental variables
 * @variable: hanlde variables
 *
 * Return: variable
 */
char *get_environment_variable(char *variable)
{
	return (getenv(variable));
}
