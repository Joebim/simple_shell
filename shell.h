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

#define MAX_PATH_LEN 256
#define MAX_ARGS 10

/* Function Prototype */
void print_error(const char *command);
char *read_input(size_t *bufsize);
int parse_input(char *input, char *args[MAX_ARGS]);
void fork_and_execute(char *args[MAX_ARGS], char *envp[]);
int custom_strcmp(const char *s1, const char *s2);
void *custom_memcpy(void *dest, const void *src, size_t n);
bool cmd_exists(char *command, char *envp[]);
char *strings_concat(const char *str1, const char *str2);
char *custom_strcpy(char *dest, const char *src);
char *custom_strcat(char *dest, const char *src);
size_t custom_strlen(const char *str);
int custom_strncmp(const char *s1, const char *s2, size_t n);

void _execute(char *prompt, char *argv[], char *envp[]);
void _printenv(void);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _isWhiteSpace(const char *prompt);
void _cd(char *args[]);
void _pexit(char *prompt);
char **_tokenize(char *prompt, char *delim);
char *get_path(char *command);

#endif
