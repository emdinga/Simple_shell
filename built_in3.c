#include "shell.h"
/**
 * alias_builtin - function to initialize aliases
 * @argc: argument count
 * @argv: argument vector
 * @info: argument info
 *
 * Return: 0 on success or 1 on error
 */
int alias_builtin(int argc, char **argv, info_t *info)
{
	int j = 0;
	const struct Alias *alias = NULL;
	char *p = strchr(argv[j], '=');

	if (argc == 1)
	{
		for (j = 0; j < MAX_ALIASES; j++)
		{
			print_alias(&Aliases[j]);
		}
		return (0);
	}
	for (j = 1; j < argc; j++)
	{
		if (p)
		{
			*p = '\0';
			set_alias(info, argv[j]);
		}
		else
		{
			alias = find_alias(&argv[j]);
			print_alias(alias);
		}
	}
	return (0);
}
/**
 * delete_alias - Function delete from the aliases array
 * @name: name of an alias
 *
 * Return:0 on success or 1 on error
 */
int delete_alias(const char *name)
{
	int a;
	int b;
	int f = 0;
	struct Aliases *new_aliases;

	for (a = 0, b = 0; a < num_aliases; a++)
	{
		if (strcmp(Aliases[a].name, name) != 0)
		{
			Aliases[b] = Aliases[a];
			b++;
		}
		else
		{
			f = 1;
		}
	}
	if (f)
	{
		num_aliases--;
		new_aliases = realloc(Aliases, sizeof(struct Alias) * num_aliases);
		if (new_aliases == NULL)
		{
			fprintf(stderr, "memory allocation error\n");
			return (1);
		}
		memcpy(Aliases, new_aliases, sizeof(struct Alias) * num_aliases);
		free(new_aliases);
	}
	return (0);
}
/**
 * find_alias - Funtion to find aliases array
 * @argv: pointer to an alias
 *
 * Return: a pointer if it exist or NULL
 */
const struct Alias *find_alias(char **argv)
{
	const char *name = argv[0];
	int j;

	for (j = 0; j < num_aliases; j++)
	{
		if (strcmp(Aliases[j].name, name) == 0)
		{
			return (&Aliases[j]);
		}
	}
	return (NULL);
}
/**
 * add_alias - Funtion that adds a new alias to the aliases array
 * @name: pointer to the alias name
 * @value: pointer to the value of the alias
 * @alias: node for an alias name
 * Return: 0 on success or -1 on failure
 */
int add_alias(list_t **alias, const char *name, const char *value)
{
	list_t *new_alias = malloc(sizeof(list_t));

	if (new_alias == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return (1);
	}
	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = NULL;
	if (*alias == NULL)
	{
		*alias = new_alias;
	}
	else
	{
		list_t *current = *alias;

		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_alias;
	}
	return (0);
}
