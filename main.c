#include "shell.h"
/**
 * main - shell entry function
 * @argc: argument count
 * @argv: argument vector
 * @envp: emvironment variables
 * Return: 0 for SUCCESS
 */
int main(int argc, char *argv[], char *envp[])
{
	char buf[] = "cisfun$ ", *prompt = NULL, *command = NULL;
	size_t input_len = 0;
	ssize_t len;
	char **tok, *delim = " ";
	int i;

	(void) argc;
	(void) argv;
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, buf, sizeof(buf));
		fflush(stdin);
		len = _getline(&prompt, &input_len, stdin);
		if (len == -1)
			exit_shell(prompt);
		if (len > 1 && prompt != NULL)
		{
			if (is_white_space(prompt) == 1)
				exit_shell(prompt);
			if (strcmp(prompt, "exit\n") == 0)
				exit_shell(prompt);
			command = strtok(prompt, "\n");
			while (command != NULL)
			{
				tok = get_token(command, delim);
				_exec(tok[0], tok, envp);
				for (i = 0; tok[i] != NULL; i++)
					free(tok[i]);
				free(tok);
				command = strtok(NULL, "\n");
			}
			tok = NULL;
			free(prompt);
			prompt = NULL;
		}
	}
	return (0);
}

/**
 * exit_shell - exit the shell
 * @prompt: pointer to the prompt
 */
void exit_shell(char *prompt)
{
	free(prompt);
	exit(EXIT_SUCCESS);
}

/**
 * get_token - breaks strings to tok
 * @prompt: pointer to string
 * @delim: string delimiter
 * Return: pointer to array of strings
 */
char **get_token(char *prompt, char *delim)
{
	char **tok;
	int count = 0, i = 0;
	char *temp = strdup(prompt);
	char *t = strtok(temp, delim);

	while (t != NULL)
	{
		count++;
		t = strtok(NULL, delim);
	}
	free(temp);

	tok = malloc((count + 1) * sizeof(char *));
	t = strtok(prompt, delim);
	while (t != NULL)
	{
		tok[i] = strdup(t);
		i++;
		t = strtok(NULL, delim);
	}
	tok[i] = NULL;
	return (tok);
}

/**
 * _exec - executes shell commands
 * @prompt: pointer to string command
 * @argv: argument vector
 * @envp: environment variables
 * Return: void
 */
void _exec(char *prompt, char *argv[], char *envp[])
{
	int status;
	pid_t pid;
	char *inputCommand;

	if (strcmp(prompt, "env") == 0)
	{
		get_env();
		return;
	}

	if (strcmp(prompt, "exit") == 0)
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

	pid = fork();

	if (pid == 0)
	{
		inputCommand = path_get(prompt);
		if (inputCommand == NULL)
			exit(EXIT_FAILURE);
		execve(inputCommand, argv, envp);
		perror(inputCommand);
		exit(EXIT_SUCCESS);
	}
	else
	{
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
}

/**
 * path_get - gets or fetches the PATH of a file
 * @command: the PATH to be found
 * Return: an array of string.
 */
char *path_get(char *command)
{
	char *path_cpy;
	int cmd_length;
	char *path_token;
	int dir_len;
	char *fpath;
	struct stat buffer;
	char *path = getenv("PATH");

	if (path)
	{
		path_cpy = strdup(path);
		cmd_length = strlen(command);
		path_token = strtok(path_cpy, ":");

		while (path_token != NULL)
		{
			dir_len = strlen(path_token);
			fpath = malloc(cmd_length + dir_len + 2);
			strcpy(fpath, path_token);
			strcat(fpath, "/");
			strcat(fpath, command);
			strcat(fpath, "\0");
			if (stat(fpath, &buffer) == 0)
			{
				free(path_cpy);
				return (fpath);
			}
			else
			{
				free(fpath);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_cpy);
		if (stat(command, &buffer) == 0)
			return (command);
		return (command);
	}
	return (command);
}
