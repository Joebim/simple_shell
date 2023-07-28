#include "shell.h"

/**
 * hist - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @num: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int hist(num_t *num)
{
	int_print(num->history);
	return (0);
}

/**
 * undo_user - sets alias to string
 * @num: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int undo_user(num_t *num, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = node_del(&(num->alias),
		find_index_n(num->alias, node_sw(num->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * make_user - sets alias to string
 * @num: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int make_user(num_t *num, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (undo_user(num, str));

	undo_user(num, str);
	return (input_limit(&(num->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * set_user - mimics the alias builtin (man alias)
 * @num: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int set_user(num_t *num)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (num->argc == 1)
	{
		node = num->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; num->argv[i]; i++)
	{
		p = _strchr(num->argv[i], '=');
		if (p)
			make_user(num, num->argv[i]);
		else
			print_alias(node_sw(num->alias, num->argv[i], '='));
	}

	return (0);
}

