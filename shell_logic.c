#include "shell.h"

/**
 * trim_whitespace - Trim leading and trailing whitespace from a string.
 * @str: string to be trimmed.
 *
 * Return: The trimmed string.
 */
char *trim_whitespace(char *str)
{
	char *end = str + strlen(str) - 1;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str == ' ' || *str == '\t')
	{
		str++;
	}
	while (end > str && (*end == ' ' || *end == '\t'))
	{
		end--;
	}
	*(end + 1) = '\0';
	return (str);
}
/**
 * handle_comments - Remove comments from the command.
 * @command: The command to be processed.
 *
 * Return: 0
 */
void handle_comments(char *command)
{
	char *c_pos = strchr(command, '#');
	char *t_command = trim_whitespace(command);

	if (command == NULL || *command == '\0')
	{
		return;
	}
	if (*command == '#')
	{
		return;
	}
	if (*t_command == '\0')
	{
		*c_pos = '\0';
	}
}
/**
 * handle_separator - function to hanlde command separation
 * @command: a command to be processed.
 *
 * Return: 0
 */
void handle_separator(char *command)
{
	char *s_pos = strchr(command, ';');
	char *t_command = trim_whitespace(command);

	if (command == NULL || *command == '\0')
	{
		return;
	}
	if (*command == ';')
	{
		return;
	}
	if (*t_command == '\0')
	{
		*s_pos = '\0';
	}
}
/**
 * handle_logical_operators - Handle logical operators
 * @command: a command to be processed.
 *
 * Return: 0
 */
void handle_logical_operators(char *command)
{
	char *and_pos = strstr(command, "&&");
	char *or_pos = strstr(command, "||");
	char *t_command = trim_whitespace(command);

	if (command == NULL || *command == '\0')
	{
		return;
	}
	if (and_pos != NULL)
	{
		*and_pos = '\0';
	}
	else if (or_pos != NULL)
	{
		*or_pos = '\0';
	}
	else if (*t_command == '\0')
	{
		return;
	}
}
/**
 * execute_commands_from_file - Funtion to execute commands from a file.
 * @filename: name of the file
 *
 * Return: 0
 */
void execute_commands_from_file(char *filename)
{
	FILE *file = fopen(filename, "r");
	char line[256];
	size_t read = strlen(line);

	if (file == NULL)
	{
		printf("Failed to open file: %s\n", filename);
		return;
	}
	while (fgets(line, sizeof(line), file))
	{
		if (read > 0 && line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}
		handle_command(line);
	}
	fclose(file);
}
