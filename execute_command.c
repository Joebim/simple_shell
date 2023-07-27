#include "shell.h"
/**
 * execute_command - Execute the command using the PATH.
 * @command: pointer to the command
 * @argv: argument vector
 * @envp: environment variables
 */
void execute_command(char *command, char *argv[], char *envp[])
{
	char *actual_command, **flags;
	pid_t pid;
	char *inputCommand = path_get(command);

	parse_flags(argv, &actual_command, &flags);
	if (actual_command != NULL)
	{
		execute_command_with_flags(actual_command, flags, envp);
		exit(EXIT_SUCCESS);
	}
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

/**
 * execute_command_with_flags - Execute the command using the PATH with flags.
 * @command: pointer to the command
 * @flags: array of flags
 * @envp: environment variables
 */
void execute_command_with_flags(char *command, char *flags[], char *envp[])
{
	pid_t pid;
	char *inputCommand = path_get(command);
	char **command_with_flags;

	if (prepare_command_with_flags(command, flags, &command_with_flags) == -1)
		return;

	pid = fork();
	if (pid == 0)
	{
		execve(inputCommand, command_with_flags, envp);
		perror(inputCommand);
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		wait(&status);
		if (WIFEXITED(status))
		{
			int exitStatus = WEXITSTATUS(status);

			if (exitStatus != 0)
				exit(exitStatus);
		}
		else if (WIFSIGNALED(status))
		{
			int signalNumber = WTERMSIG(status);

			exit(128 + signalNumber);
		}
	}
	free(command_with_flags);
}

/**
 * parse_flags - Function to parse command-line arguments and separate
 *               flags from the command.
 *
 * @argv: The argument vector containing command-line arguments.
 * @command: Pointer to store the extracted command from argv[0].
 * @flags: Pointer to store the extracted flags from argv[1...n].
 */
void parse_flags(char *argv[], char **command, char ***flags)
{
	int i, j;
	int flags_count = 0;
	*command = argv[0];
	*flags = NULL;

	for (i = 1; argv[i] != NULL && argv[i][0] == '-'; i++)
	{
		flags_count++;
	}
	if (flags_count > 0)
	{
		*flags = malloc(sizeof(char *) * (flags_count + 1));
		if (*flags == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		for (j = 0; j < flags_count; j++)
		{
			(*flags)[j] = argv[j + 1];
		}

		(*flags)[flags_count] = NULL;
	}
}
