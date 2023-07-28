#include "shell.h"

/**
 * exit_c - exits the shell
 * @num: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if num.argv[0] != "exit"
 */
int exit_c(num_t *num)
{
	int exitc;

	if (num->argv[1]) /* If there is an exit arguement */
	{
		exitc = convert_err(num->argv[1]);
		if (exitc == -1)
		{
			num->status = 2;
			print_error(num, "Illegal number: ");
			char_put(num->argv[1]);
			char_print('\n');
			return (1);
		}
		num->err_num = convert_err(num->argv[1]);
		return (-2);
	}
	num->err_num = -1;
	return (-2);
}

/**
 * cmd_cd - changes the current folderectory of the process
 * @num: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int cmd_cd(num_t *num)
{
	char *s, *folder, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!num->argv[1])
	{
		folder = _getenv(num, "HOME=");
		if (!folder)
			chdir_ret = /* TODO: what should this be? */
				chdir((folder = _getenv(num, "PWD=")) ? folder : "/");
		else
			chdir_ret = chdir(folder);
	}
	else if (_strcmp(num->argv[1], "-") == 0)
	{
		if (!_getenv(num, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(num, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((folder = _getenv(num, "OLDPWD=")) ? folder : "/");
	}
	else
		chdir_ret = chdir(num->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(num, "can't cd to ");
		char_put(num->argv[1]), char_print('\n');
	}
	else
	{
		_setenv(num, "OLDPWD", _getenv(num, "PWD="));
		_setenv(num, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * set_h - changes the current folderectory of the process
 * @num: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int set_h(num_t *num)
{
	char **arr_num;

	arr_num = num->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arr_num); /* temp att_unused workaround */
	return (0);
}

