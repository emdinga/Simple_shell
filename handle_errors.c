#include "shell.h"
/**
 * handle_errors - function to handle error conditions
 * Return: 0
 */
void handle_errors(void)
{
	char error[100];

	snprintf(error, sizeof(error), "Error: %s", strerror(errno));
	perror(error);
	exit(EXIT_FAILURE);
}
/**
 * handle_eof - function to handle end of file condition
 * Return: 0
 */
void handle_eof(void)
{
	printf("\n");
	exit(EXIT_SUCCESS);
}

/**
 * split_line - Split a line into tokens
 * @line: The line to be split
 *
 * Return: An array of tokens
 */
char **split_line(char *line)
{
	char **tokens = malloc(MAX_TOKENS * sizeof(char *));
	char *t;
	int t_count = 0;

	if (tokens == NULL)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}
	t = strtok(line, TOKEN_DELIMITERS);
	while (t != NULL)
	{
		tokens[t_count] = t;
		t_count++;
		if (t_count >= MAX_TOKENS)
		{
			fprintf(stderr, "Too many tokens\n");
			exit(EXIT_FAILURE);
		}
		t = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[t_count] = NULL;
	return (tokens);
}
/**
 * free_args - Free the memory allocated for an array of arguments
 * @args: The array of arguments to free
 *
 * Return: free args
 */
void free_args(char **args)
{
	int j = 0;

	if (args == NULL)
		return;
	while (args[j] != NULL)
	{
		free(args[j]);
		j++;
	}
	free(args);
}
