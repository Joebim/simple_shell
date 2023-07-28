
#include "shell.h"

/**
 * get_history_file - gets the history file
 * @num: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(num_t *num)
{
	char *buf, *folder;

	folder = _getenv(num, "HOME=");
	if (!folder)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(folder) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, folder);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @num: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(num_t *num)
{
	ssize_t fd;
	char *filename = get_history_file(num);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = num->history; node; node = node->next)
	{
		print_formats(node->str, fd);
		print_format('\n', fd);
	}
	print_format(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @num: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(num_t *num)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(num);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(num, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(num, buf + last, linecount++);
	free(buf);
	num->histcount = linecount;
	while (num->histcount-- >= HIST_MAX)
		node_del(&(num->history), 0);
	renumber_history(num);
	return (num->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @num: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(num_t *num, char *buf, int linecount)
{
	list_t *node = NULL;

	if (num->history)
		node = num->history;
	input_limit(&node, buf, linecount);

	if (!num->history)
		num->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @num: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(num_t *num)
{
	list_t *node = num->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (num->histcount = i);
}

