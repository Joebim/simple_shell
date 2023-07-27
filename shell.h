#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

extern char **environ;

/* Function Prototype */
void execute_command(char *command, char *argv[], char *envp[]);
void _exec(char *prompt, char *argv[], char *envp[]);
void get_env(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int is_white_space(const char *prompt);
void nav_dir(char *args[]);
void exit_shell(char *prompt);
char **get_token(char *prompt, char *delim);
char *path_get(char *command);
int exit_check(char *argv[]);
void execute_command_with_flags(char *command, char *flags[], char *envp[]);
void parse_flags(char *argv[], char **command, char ***flags);
int prepare_flags(char *command, char *flags[], char **command_with_flags[]);

#endif
