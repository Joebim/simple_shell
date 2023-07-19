#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * custom_strcmp - Compares two strings
 * @str1: The first string to compare
 * @str2: The second string to compare
 *
 * Return: 0 if the strings are equal, a negative value if str1 is less than str2,
 *         a positive value if str1 is greater than str2
 */
int custom_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * read_input - Reads user input from stdin
 * @bufsize: Pointer to the buffer size for getline
 *
 * Return: A pointer to the allocated buffer containing the user input
 */
char *read_input(size_t *bufsize)
{
    char *buf = NULL;
    if (getline(&buf, bufsize, stdin) == -1)
    {
        perror("getline");
        exit(EXIT_FAILURE);
    }
    return buf;
}

/**
 * parse_input - Parses user input into arguments
 * @input: The user input to parse
 * @args: Array to store the parsed arguments
 *
 * Return: The number of arguments parsed
 */
int parse_input(char *input, char *args[MAX_ARGS])
{
    int num_args = 0;
    char *token = strtok(input, " ");
    while (token != NULL && num_args < MAX_ARGS - 1)
    {
        args[num_args++] = token;
        token = strtok(NULL, " ");
    }
    args[num_args] = NULL; /* Set the last element to NULL for execve */
 
    return num_args;
}

/**
 * is_exit_command - Checks if the command is "exit"
 * @args: Array of arguments to check
 *
 * Return: 1 if the command is "exit", 0 otherwise
 */
int is_exit_command(char *args[MAX_ARGS])
{
    return (args[0] != NULL && custom_strcmp(args[0], "exit") == 0);
}

/**
 * main - Display a prompt and wait for the user to type a command
 * A command line always ends with a new line
 * @argc: argumen count (unused).
 * @argv: argument vector (unused).
 * Return: always 0 (success).
 */

/**
 * fork_and_execute - Forks and executes the command
 * @args: Array of arguments for the command
 */
void fork_and_execute(char *args[MAX_ARGS], char *executable)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, NULL) == -1)
        {
            print_error(executable);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL); /* Wait for the child process to finish */
    }
}


/**
 * main - Main function for the simple shell
 * @argc: Argument count (unused)
 * @argv: Argument vector (unused)
 *
 * Return: Always 0 (success)
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
    

	size_t bufsize = 32;
    char *buf;
    char *args[MAX_ARGS]; /* Array to store command and arguments */
    char *input;
    int num_args __attribute__((unused)); /* Variable to store the number of arguments */

    /* Allocate memory for the input buffer */
    buf = (char *)malloc(bufsize * sizeof(char));

    /* Main shell loop */
    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        /* Read user input */
        input = read_input(&bufsize);

        /* Check for the "exit" command to terminate the shell */
        if (is_exit_command(args))
        {
            free(buf);
            free(input);
            exit(EXIT_SUCCESS);
        }


        /* Parse the input into arguments */
        num_args = parse_input(input, args);

        /* Fork and execute the command */
        fork_and_execute(args, argv[0]);

        /* Free dynamically allocated memory for input */
        free(input);
    }

    /* Free dynamically allocated memory for the buffer */
    free(buf);
    return (0);
}
