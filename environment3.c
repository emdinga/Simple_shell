#include "shell.h"
/**
 * convert_pid_to_string - function to convert pid to string
 * @pid: handles pid
 *
 * Return: a converted string
 */
char *convert_pid_to_string(pid_t pid)
{
	int n_digits = 0;
	char *pid_str = NULL;
	pid_t temp = pid;

	while  (temp != 0)
	{
		temp /= 10;
		n_digits++;
	}
	pid_str = (char *)malloc((n_digits + 1) * sizeof(char));
	if (pid_str == NULL)
	{
		fprintf(stderr, "Failed \n");
		return (NULL);
	}
	snprintf(pid_str, n_digits + 1, "%d", pid);
	return (pid_str);
}
/**
 * set_environment_variable - function set environment for pid
 * @name: pointer to the varaible name
 * @value: pointer to the value of the varaible
 *
 * Return: 0 or -1
 */
int set_environment_variable(const char *name, const char *value)
{
	size_t l = strlen(name) + strlen(value) + 2;
	char *env = (char *)malloc(l * sizeof(char));

	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Invalid: name or value is NULL\n");
		return (-1);
	}

	if (env == NULL)
	{
		fprintf(stderr, "Failed to allocete memory\n");
		return (-1);
	}
	snprintf(env, l, "%s=%s", name, value);
	if (putenv(env) != 0)
	{
		fprintf(stderr, "Failed to set environment: %s\n", name);
		free(env);
		return (-1);
	}
	return (0);
}
/**
 * handle_command - function to handle a single command.
 * @command: command to handle
 *
 * Return: 0
 */
void handle_command(char *command)
{
	if (command == NULL || *command == '\0')
	{
		return;
	}
	printf("Executing command: %s\n", command);
}
/**
 * handle_pid_variable - Main function to handle pid values
 * Return: 0
 */
void handle_pid_variable(void)
{
	pid_t pid = getpid();
	char *pid_str = convert_pid_to_string(pid);

	set_environment_variable("PID", pid_str);
	printf("PID: %s\n", pid_str);
	free(pid_str);
}
