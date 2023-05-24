#include "shell.h"
/**
 * convert_exit_status_to_string - main function
 * @exit_status: parameter value
 * Return: 0
 */
char *convert_exit_status_to_string(int exit_status)
{
	char *exit_status_str = malloc(16);

	snprintf(exit_status_str, 16, "%d", exit_status);
	return (exit_status_str);
}
/**
 * extract_directory - Extracts the directory path
 * @path: The file path
 * @length: A pointer to an integer
 *
 * Return: A string containing the extracted directory path or NULL
 */
char *extract_directory(char *path, int *length)
{
	char *dir = NULL;
	int a, b;

	if (path == NULL || *path == '\0')
		return (NULL);
	for (a = 0, b = -1; path[a] != '\0'; a++)
	{
		if (path[a] == '/')
			b = a;
	}
	if (b == -1)
		return (NULL);
	dir = malloc(b + 2);
	if (dir == NULL)
		return (NULL);
	strncpy(dir, path, b + 1);
	dir[b + 1] = '\0';
	if (length != NULL)
		*length = b + 1;
	return (dir);
}
/**
 * construct_command - Constructs the command
 * @directory: directory path
 * @command: command name
 *
 * Return: A newly allocated string containing the constructed command or NULL
 */
char *construct_command(char *directory, char *command)
{
	char *c;
	size_t d_len, cmd_len;

	if (directory == NULL || command == NULL)
		return (NULL);
	d_len = strlen(directory);
	cmd_len = strlen(command);
	c = malloc(d_len + cmd_len + 2);
	if (c == NULL)
		return (NULL);
	strcpy(c, directory);
	if (c[d_len - 1] != '/')
		strcat(c, "/");
	strcat(c, command);
	return (c);
}
/**
 * resolve_path - Resolves the absolute path of a command
 * @command: command name
 *
 * Return: string containing the absolute path of the command or NULL
 */
char *resolve_path(char *command)
{
	char *path = getenv("PATH");
	char *token, *dir, *p_copy;
	char *r_path = NULL;

	if (command == NULL || path == NULL)
		return (NULL);
	p_copy = strdup(path);
	if (p_copy == NULL)
		return (NULL);
	token = strtok(p_copy, ":");
	while (token != NULL)
	{
		dir = construct_command(token, command);
		if (dir != NULL)
		{
			if (access(dir, F_OK) == 0)
			{
				r_path = strdup(dir);
				free(dir);
				break;
			}
			free(dir);
			break;
		}
		token = strtok(NULL, ":");
	}
	free(p_copy);
	return (r_path);
}
/**
 * get_exit_status - exit status of the last executed command
 * @status: exit status
 * Return: exit status of the last executed command
 */
int get_exit_status(int status)
{
	if (WIFEXITED(status))
	{
		return (WEXITSTATUS(status));
	}
	return (-1);
}
