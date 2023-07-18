#include "shell.h"

/**
 * clear_arg - initializes arg_t struct
 * @arg: struct address
 */
void clear_arg(arg_t *arg)
{
	arg->arg = NULL;
	arg->argv = NULL;
	arg->path = NULL;
	arg->argc = 0;
}

/**
 * set_arg - initializes arg_t struct
 * @arg: struct address
 * @av: argument vector
 */
void set_arg(arg_t *arg, char **av)
{
	int i = 0;

	arg->fname = av[0];
	if (arg->arg)
	{
		arg->argv = strtow(arg->arg, " \t");
		if (!arg->argv)
		{
			arg->argv = malloc(sizeof(char *) * 2);
			if (arg->argv)
			{
				arg->argv[0] = _strdup(arg->arg);
				arg->argv[1] = NULL;
			}
		}
		for (i = 0; arg->argv && arg->argv[i]; i++)
			;
		arg->argc = i;

		replace_alias(arg);
		replace_vars(arg);
	}
}

/**
 * free_arg - frees arg_t struct fields
 * @arg: struct address
 * @all: true if freeing all fields
 */
void free_arg(arg_t *arg, int all)
{
	ffree(arg->argv);
	arg->argv = NULL;
	arg->path = NULL;
	if (all)
	{
		if (!arg->cmd_buf)
			free(arg->arg);
		if (arg->env)
			free_list(&(arg->env));
		if (arg->history)
			free_list(&(arg->history));
		if (arg->alias)
			free_list(&(arg->alias));
		ffree(arg->environ);
			arg->environ = NULL;
		bfree((void **)arg->cmd_buf);
		if (arg->readfd > 2)
			close(arg->readfd);
		_putchar(BUF_FLUSH);
	}
}

