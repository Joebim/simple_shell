
#include "shell.h"
/**
 * prepare_flags - Prepare the command array with flags.
 * @command: pointer to the command
 * @flags: array of flags
 * @command_with_flags: pointer to the array to store the result
 * Return: 0 on success, -1 on failure
 */
int prepare_flags(char *command, char *flags[], char **command_with_flags[])
{
	char *inputCommand = path_get(command);
	int i;
	int num_flags;

	if (inputCommand == NULL)
	{
		perror("Command not found in PATH");
		return (-1);
	}
	num_flags = 0;

	if (flags != NULL)
	{
		while (flags[num_flags] != NULL)
			num_flags++;
	}

	*command_with_flags = malloc((num_flags + 2) * sizeof(char *));
	if (*command_with_flags == NULL)
	{
		perror("Memory allocation error");
		return (-1);
	}

	(*command_with_flags)[0] = inputCommand;
	for (i = 0; i < num_flags; i++)
		(*command_with_flags)[i + 1] = flags[i];
	(*command_with_flags)[num_flags + 1] = NULL;

	return (0);
}
