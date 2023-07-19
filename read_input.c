#include <stdio.h>
#include <stdlib.h>

/**
 * read_input - Reads user input from stdin
 * @bufsize: Pointer to the buffer size for getline
 *
 * Return: A pointer to the allocated buffer containing the user input
 */

char *read_input(size_t *bufsize)
{
	char *buf = NULL;

	if (getline(&buf, bufsize, stdin) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (buf);
}
