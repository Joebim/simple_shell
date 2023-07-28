#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	num_t num[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				char_put(av[0]);
				char_put(": 0: Can't open ");
				char_put(av[1]);
				char_print('\n');
				char_print(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		num->readfd = fd;
	}
	env_store(num);
	read_history(num);
	hsh(num, av);
	return (EXIT_SUCCESS);
}
