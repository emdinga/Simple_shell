#include "shell.h"

/**
 * display_prompt - Main funtion to prompt the user
 * Return: 0
 */

void display_prompt(void)
{
	char *p = "$ ";
	ssize_t p_length = strlen(p);

	ssize_t  b_written = write(STDOUT_FILENO, p, p_length);

	if (b_written == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}
/**
 * read_command - MAin function to read the input
 * Return: 0
 */

char *read_command(void)
{
	char *command = malloc(MAX_INPUT_LENGTH);
	size_t c_length = strlen(command);

	if (command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	if (fgets(command, MAX_INPUT_LENGTH, stdin) == NULL)
	{
		free(command);
		return (NULL);
	}

	if (c_length > 0 && command[c_length - 1] == '\n')
	{
		command[c_length - 1] = '\0';
	}
	return (command);
}
