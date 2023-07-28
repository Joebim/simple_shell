#include "shell.h"

/**
 * env_p - returns the string array copy of our environ
 * @num: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **env_p(num_t *num)
{
	if (!num->environ || num->env_changed)
	{
		num->environ = convert_list(num->env);
		num->env_changed = 0;
	}

	return (num->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @num: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(num_t *num, char *var)
{
	list_t *node = num->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			num->env_changed = node_del(&(num->env), i);
			i = 0;
			node = num->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (num->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @num: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(num_t *num, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = num->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			num->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	input_limit(&(num->env), buf, 0);
	free(buf);
	num->env_changed = 1;
	return (0);
}


