#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 10

/* Function Prototype */
void print_error(const char *command);
int cus_strcmp(const char *str1, const char *str2);
char *read_input(size_t *bufsize);
int parse_input(char *input, char *args[MAX_ARGS]);
void fork_and_execute(char *args[MAX_ARGS], char *executable);

#endif
