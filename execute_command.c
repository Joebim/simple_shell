#include "shell.h"

/**
 * execute_command - Execute the command using the PATH.
 * @command: pointer to the command
 * @argv: argument vector
 * @envp: environment variables
 */
void execute_command(char *command, char *argv[], char *envp[])
{
	pid_t pid;
	char *inputCommand = path_get(command);

	if (inputCommand == NULL)
		exit(EXIT_FAILURE);

	pid = fork();
	if (pid == 0)
	{
		execve(inputCommand, argv, envp);
		perror(inputCommand);
		exit(EXIT_SUCCESS);
	} else
	{
		int status;

		wait(&status);
		if (WIFEXITED(status))
	{
		int exitStatus = WEXITSTATUS(status);

		if (exitStatus != 0)
			exit(exitStatus);
	} else if (WIFSIGNALED(status))
	{
		int signalNumber = WTERMSIG(status);

		exit(128 + signalNumber);
	}
	}
}
