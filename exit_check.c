#include "shell.h"

/**
 * exit_check - handles the exit command
 * @argv: argument vector
 * Return: exit status
 */

int exit_check(char *argv[])
{
		if (argv[1] != NULL)
		{
			int exitStatus = atoi(argv[1]);

			exit(exitStatus);
		}
		else
		{
			exit(EXIT_SUCCESS);
		}
}
