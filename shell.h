#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 10
#define BUFFER_SIZE 1024
#define MAX_TOKENS 64
#define TOKEN_DELIMITERS " \t\n\r\a"
#define MAX_ALIASES 10

/**
 * struct Alias - Structure representing an alias.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: holds the next value
 *
 * This structure holds information about an alias used in the shell.
 */
typedef struct Alias
{
	char *name;
	char *value;
	struct Alias *next;
} Alias;

extern Alias Aliases[MAX_ALIASES];
/**
 * struct list_s - struct for list
 * @name: the name of the list
 * @alias: alias value
 * @value: value of the list
 * @next: next value
 *
 */
typedef struct list_s
{
	struct Alias *alias;
	char *name;
	char *value;
	struct list_s *next;
} list_t;
/**
 * struct info_s - struct for info
 * @alias: pointer of an alias
 * @argc: parameter value
 * @argv: parameter value
 *
 */
typedef struct info_s
{
	list_t *alias;
	int argc;
	char **argv;
} info_t;

extern int num_aliases;


extern char **environ;

void display_prompt(void);
char *read_command(void);
char **parse_command(char *command, int *num_args);
void execute_command(char **args);
int command_exists(char *command);
void handle_errors(void);
void handle_eof(void);
void handle_path(char **args);
void handle_variables(char **args, int num_args, int status);
void handle_exit_status(int status);
void handle_pid_variable(void);
void handle_comments(char *command);
void handle_separator(char *command);
void handle_logical_operators(char *command);
void execute_commands_from_file(char *filename);
void handle_shell_arguments(int argc, char **argv);
void shell_loop(void);

/*environment*/
char *convert_exit_status_to_string(int exit_status);
char *get_environment_variable(char *variable);
char *extract_directory(char *path, int *length);
char *construct_command(char *directory, char *command);
char *resolve_path(char *command);
int get_exit_status(int status);
int set_environment_variable(const char *name, const char *value);
char *convert_pid_to_string(pid_t pid);
void handle_command(char *command);
char *read_line(void);
char **split_line(char *line);
void free_args(char **args);

/*BUILTIN*/
void exit_builtin(char **args);
void env_builtin(void);
char *custom_getline(void);
int cd_builtin(const char *directory);
int unset_env(const char *variable);
int set_env(const char *variable, const char *value);
int convert_string(const char *str);
int delete_alias(const char *name);
int set_alias(info_t *info, char *str);
const struct Alias *find_alias(char **argv);
int alias_builtin(int argc, char **argv, info_t *info);
int print_alias(const struct Alias *alias);
int update_alias(list_t *alias, const char *name, const char *value);
int add_alias(list_t **alias, const char *name, const char *value);

#endif
