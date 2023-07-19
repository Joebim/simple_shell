#include "shell.h"
#include <string.h>

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
	/* Set the last element to NULL for execve */
	args[num_args] = NULL;

	return (num_args);
}
