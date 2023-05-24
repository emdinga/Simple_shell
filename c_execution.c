#include "shell.h"
/**
 * parse_command - function parses a command string into an array of arguments
 * @command: 1st parameter value
 * @n_args: 2nd parameter value
 *
 * Return: args
 */
char **parse_command(char *command, int *n_args)
{
	char **args = malloc((MAX_ARGS + 1) * sizeof(char *));
	char *t;
	int j = 0;

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	t = strtok(command, " ");
	while (t != NULL)
	{
		args[j] = strdup(t);
		if (args[j] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		j++;
		t = strtok(NULL, " ");
	}
	args[j] = NULL;
	*n_args = j;
	return (args);
}
/**
 * execute_command -  function creates a child process using fork()
 * @args: to handle arguments
 *
 * Return: 0
 */

void execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
			handle_errors();
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		handle_errors();
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
/**
 * check_command - function checks if a given command exists in the directories
 * @command: pointer to arguments
 *
 * Return: 0 or 1
 */
int check_command(char *command)
{
	char *path = getenv("PATH");
	char *token;
	char *full_path;

	while ((token = strtok(path, ":")) != NULL)
	{
		path = NULL;
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			free(full_path);
			return (1);
		}
		free(full_path);
	}
	return (0);
}
