#include "shell.h"
/**
 * exit_builtin - Function to handle the exit built-in command
 * @args: Array of arguments passed
 *
 * Return: exit status
 */
void exit_builtin(char **args)
{
	int s = 0;

	if (args[1] != NULL)
	{
		s = convert_string(args[1]);
		if (s == 0 && strcmp(args[1], "0") != 0)
		{
			fprintf(stderr, "Invalid status value: %s\n", args[1]);
			return;
		}
	}

	exit(s);
}
/**
 * env_builtin - Handle the env built-in command
 *
 * Description: This function prints the current environment variables
 * by accessing the `environ` variable.
 */
void env_builtin(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
/**
 * custom_getline - Read a line of input from the user
 *
 * Return: A pointer to the read line
 */
char *custom_getline(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t r;

	r = getline(&line, &bufsize, stdin);
	if (r == -1)
	{
		fprintf(stderr, "Error reading input\n");
		free(line);
		return (NULL);
	}
	if (line[r - 1] == '\n')
	{
		line[r - 1] = '\0';
	}
	return (line);
}
/**
 * cd_builtin - Change the current directory
 * @directory: The directory to change to
 *
 * Return: 0 on success, -1 on failure
 */
int cd_builtin(const char *directory)
{
	char *home_dir;
	const char *new_dir;
	int result;
	char cwd[4096];

	if (directory == NULL || strcmp(directory, "-") == 0)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			fprintf(stderr, "cd: $HOME not set\n");
			return (-1);
		}
		new_dir = home_dir;
	}
	else
	{
		new_dir = directory;
	}

	result = chdir(new_dir);
	if (result != 0)
	{
		fprintf(stderr, "cd: Failed to change directory to %s\n", new_dir);
		return (-1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		fprintf(stderr, "cd: Failed to get current working directory\n");
		return (-1);
	}
	if (setenv("PWD", cwd, 1) != 0)
	{
		fprintf(stderr, "cd: Failed to update PWD environment variable\n");
		return (-1);
	}

	return (0);
}
/**
 * update_alias - Funtion that updates the value of an existing alias
 * @alias: Pointer to the head of the alias list
 * @name: Name of the alias to update
 * @value: New value for the alias
 *
 * Return: 0 on success, 1 on failure
 */
int update_alias(list_t *alias, const char *name, const char *value)
{
	list_t *node;

	if (!alias || !name || !value)
		return (1);
	node = alias;
	while (node)
	{
		if (strcmp(node->name, name) == 0)
		{
			free(node->value);
			node->value = strdup(value);
			if (!node->value)
				return (1);
			return (0);
		}
		node = node->next;
	}
	return (1);
}
