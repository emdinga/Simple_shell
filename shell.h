#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void display_prompt(void);
char *read_command(void);
char **parse_command(char *command, int *num_args);
void execute_command(char **args);


#endif
