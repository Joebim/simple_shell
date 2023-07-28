#include "shell.h"

/**
 * _myenv - prints the current environment
 * @num: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(num_t *num)
{
	int_print_str(num->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @num: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(num_t *num, const char *name)
{
	list_t *node = num->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @num: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(num_t *num)
{
	if (num->argc != 3)
	{
		char_put("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(num, num->argv[1], num->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @num: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(num_t *num)
{
	int i;

	if (num->argc == 1)
	{
		char_put("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= num->argc; i++)
		_unsetenv(num, num->argv[i]);

	return (0);
}

/**
 * env_store - populates env linked list
 * @num: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_store(num_t *num)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		input_limit(&node, environ[i], 0);
	num->env = node;
	return (0);
}

