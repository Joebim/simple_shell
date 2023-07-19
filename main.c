#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * is_exit_command - Checks if the command is "exit"
 * @args: Array of arguments to check
 *
 * Return: 1 if the command is "exit", 0 otherwise
 */

int is_exit_command(char *args[MAX_ARGS])
{
	return (args[0] != NULL && cus_strcmp(args[0], "exit") == 0);
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
	/* Array to store command and arguments */
	char *args[MAX_ARGS];
	char *input;
	/* Variable to stothe number of arguments */
	int num_args __attribute__((unused));

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
