#include "shell.h"
/**
 * read_line - Read a line of input from the user
 * Return: A pointer to the read line
 */
char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;
	ssize_t read_size;

	read_size = getline(&line, &buffer_size, stdin);
	if (read_size == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	if (read_size > 0 && line[read_size - 1] == '\n')
		line[read_size - 1] = '\0';
	return (line);
}
/**
 * handle_shell_arguments - Process arguments passed to the shell
 * @argc: The number of arguments
 * @argv: An array of strings containing the arguments
 *
 * Return: 0
 */
void handle_shell_arguments(int argc, char **argv)
{
	int j;

	for (j = 1; j < argc; j++)
	{
		printf("Arguments %d: %s\n", j, argv[j]);

	}
}
/**
 * shell_loop - main loop of the shell
 *
 * Return: 0
 */
void shell_loop(void)
{
	char *line;
	char **args;

	do {
		printf("$> ");
		line = read_line();
		args = split_line(line);
		execute_command(args);
		free(line);
		free_args(args);
	} while (1);
	printf("exiting shell.\n");
}
