#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
 * print_error - Prints a custom error message to stderr
 * @command: The command that caused the error
 */

void print_error(const char *command)
{
	char errmsg[256];
	int i;

	/* Copy the error message to the buffer */
	for (i = 0; command[i] != '\0'; i++)
	{
		errmsg[i] = command[i];
	}
	errmsg[i++] = ':';
	errmsg[i++] = ' ';
	errmsg[i++] = 'N';
	errmsg[i++] = 'o';
	errmsg[i++] = ' ';
	errmsg[i++] = 's';
	errmsg[i++] = 'u';
	errmsg[i++] = 'c';
	errmsg[i++] = 'h';
	errmsg[i++] = ' ';
	errmsg[i++] = 'f';
	errmsg[i++] = 'i';
	errmsg[i++] = 'l';
	errmsg[i++] = 'e';
	errmsg[i++] = ' ';
	errmsg[i++] = 'o';
	errmsg[i++] = 'r';
	errmsg[i++] = ' ';
	errmsg[i++] = 'd';
	errmsg[i++] = 'i';
	errmsg[i++] = 'r';
	errmsg[i++] = 'e';
	errmsg[i++] = 'c';
	errmsg[i++] = 't';
	errmsg[i++] = 'o';
	errmsg[i++] = 'r';
	errmsg[i++] = 'y';
	errmsg[i++] = '\n';
	errmsg[i] = '\0';

	/* Use write to print the message to stderr */
	write(STDERR_FILENO, errmsg, strlen(errmsg));
}
