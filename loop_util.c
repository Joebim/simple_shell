#include "shell.h"

/**
 * hsh - main shell loop
 * @num: the parameter & return num struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(num_t *num, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_num(num);
		if (interactive(num))
			_puts("$ ");
		char_print(BUF_FLUSH);
		r = get_input(num);
		if (r != -1)
		{
			set_num(num, av);
			builtin_ret = find_builtin(num);
			if (builtin_ret == -1)
				find_cmd(num);
		}
		else if (interactive(num))
			_putchar('\n');
		free_num(num, 0);
	}
	write_history(num);
	free_num(num, 1);
	if (!interactive(num) && num->status)
		exit(num->status);
	if (builtin_ret == -2)
	{
		if (num->err_num == -1)
			exit(num->status);
		exit(num->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @num: the parameter & return num struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(num_t *num)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_c},
		{"env", _myenv},
		{"help", set_h},
		{"history", hist},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", cmd_cd},
		{"alias", set_user},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(num->argv[0], builtintbl[i].type) == 0)
		{
			num->line_count++;
			built_in_ret = builtintbl[i].func(num);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @num: the parameter & return num struct
 *
 * Return: void
 */
void find_cmd(num_t *num)
{
	char *path = NULL;
	int i, k;

	num->path = num->argv[0];
	if (num->linecount_f == 1)
	{
		num->line_count++;
		num->linecount_f = 0;
	}
	for (i = 0, k = 0; num->arg[i]; i++)
		if (!de_lim(num->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(num, _getenv(num, "PATH="), num->argv[0]);
	if (path)
	{
		num->path = path;
		fork_cmd(num);
	}
	else
	{
		if ((interactive(num) || _getenv(num, "PATH=")
					|| num->argv[0][0] == '/') && command_check(num, num->argv[0]))
			fork_cmd(num);
		else if (*(num->arg) != '\n')
		{
			num->status = 127;
			print_error(num, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @num: the parameter & return num struct
 *
 * Return: void
 */
void fork_cmd(num_t *num)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(num->path, num->argv, env_p(num)) == -1)
		{
			free_num(num, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(num->status));
		if (WIFEXITED(num->status))
		{
			num->status = WEXITSTATUS(num->status);
			if (num->status == 126)
				print_error(num, "Permission denied\n");
		}
	}
}

