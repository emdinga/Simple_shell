#include "shell.h"

/**
 * set_env - Set a new environment variable or modify an existing one
 * @variable: The name of the environment variable
 * @value: The value to assign to the environment variable
 *
 * Return: 0 on success, -1 on failure
 */
int set_env(const char *variable, const char *value)
{
	int r;

	if (variable == NULL || value == NULL)
	{
		fprintf(stderr, "setenv: Invalid arguments\n");
		return (-1);
	}

	r = setenv(variable, value, 1);
	if (r != 0)
	{
		fprintf(stderr, "setenv: Failed to set environment variable\n");
		return (-1);
	}

	return (0);
}

/**
 * unset_env - Remove an environment variable
 * @variable: The name of the environment variable to remove
 *
 * Return: 0 on success, -1 on failure
 */
int unset_env(const char *variable)
{
	int r;

	if (variable == NULL)
	{
		fprintf(stderr, "unsetenv: Invalid argument\n");
		return (-1);
	}

	r = unsetenv(variable);
	if (r != 0)
	{
		fprintf(stderr, "unsetenv: Failed to remove environment variable\n");
		return (-1);
	}

	return (0);
}
/**
 * unset_alias - function unsets an alias
 * @str: String value of an alias
 *
 * Return: 0 on success or 1 on erro
 */
int unset_alias(char *str)
{
	char *p, c;
	int r;

	p = strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = '\0';
	r = delete_alias(str);
	*p = c;
	return (r);
}
/**
 * set_alias - set an alias to a string
 * @str: string value of an alias
 * @info: string value of an alias
 *
 * Return: 0 on success or 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p, *n, *v;

	p = strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	*p = '\0';
	n = str;
	v = p + 1;
	if (update_alias(info->alias, n, v) == 1)
	{
		add_alias(&(info->alias), n, v);
	}
	*p = '=';
	return (0);
}
/**
 * print_alias - Function to print an alias in a form of value=name
 * @alias: string value to an alias
 *
 * Return: 0 on success or 1 on error
 */
int print_alias(const struct Alias *alias)
{
	if (alias)
	{
		printf("%s='%s'\n", alias->name, alias->value);
		return (0);
	}
	return (1);
}
