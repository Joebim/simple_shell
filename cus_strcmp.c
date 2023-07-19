/**
 * cus_strcmp - Compares two strings
 * @str1: The first string to compare
 * @str2: The second string to compare
 *
 * Return: 0 if str equals negative value, if str1 is less than str2
 * a positive value if str1 is greater than str2
 */

int cus_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
