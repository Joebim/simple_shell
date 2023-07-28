#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @num: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(num_t *num)
{
	return (isatty(STDIN_FILENO) && num->readfd <= 2);
}

/**
 * de_lim - checks if character is a limiteter
 * @c: the char to check
 * @limit: the limiteter string
 * Return: 1 if true, 0 if false
 */
int de_lim(char c, char *limit)
{
	while (*limit)
		if (*limit++ == c)
			return (1);
	return (0);
}

/**
 * alpha_check - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int alpha_check(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * int_convert - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int int_convert(char *s)
{
	int i, mark = 1, f = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			mark *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (mark == -1)
		output = -result;
	else
		output = result;

	return (output);
}

