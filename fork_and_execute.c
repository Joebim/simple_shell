#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * fork_and_execute - Forks and executes the command
 * @args: Array of arguments for the command
 * @executable: filename of executable file
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
		/* Wait for the child process to finish */
		wait(NULL);
	}
}
