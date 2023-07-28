
#include "shell.h"

/**
 * clear_num - initializes num_t struct
 * @num: struct address
 */
void clear_num(num_t *num)
{
	num->arg = NULL;
	num->argv = NULL;
	num->path = NULL;
	num->argc = 0;
}

/**
 * set_num - initializes num_t struct
 * @num: struct address
 * @av: argument vector
 */
void set_num(num_t *num, char **av)
{
	int i = 0;

	num->fname = av[0];
	if (num->arg)
	{
		num->argv = strtow(num->arg, " \t");
		if (!num->argv)
		{
			num->argv = malloc(sizeof(char *) * 2);
			if (num->argv)
			{
				num->argv[0] = _strdup(num->arg);
				num->argv[1] = NULL;
			}
		}
		for (i = 0; num->argv && num->argv[i]; i++)
			;
		num->argc = i;

		replace_alias(num);
		replace_vars(num);
	}
}

/**
 * free_num - frees num_t struct fields
 * @num: struct address
 * @all: true if freeing all fields
 */
void free_num(num_t *num, int all)
{
	ffree(num->argv);
	num->argv = NULL;
	num->path = NULL;
	if (all)
	{
		if (!num->cmd_buf)
			free(num->arg);
		if (num->env)
			free_list(&(num->env));
		if (num->history)
			free_list(&(num->history));
		if (num->alias)
			free_list(&(num->alias));
		ffree(num->environ);
			num->environ = NULL;
		bfree((void **)num->cmd_buf);
		if (num->readfd > 2)
			close(num->readfd);
		_putchar(BUF_FLUSH);
	}
}
