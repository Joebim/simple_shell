#include <stdio.h>
#include <stdlib.h>
/**
 * main - Display a prompt and wait for the user to type a command
 * A command line always ends with a new line
 * @argc: argumen count (unused).
 * @argv: argument vector (unused).
 * Return: always 0 (success).
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
size_t bufsize = 32;
char *buf;
buf = (char *)malloc(bufsize *  sizeof(char));
while (buf)
{
printf("#cisfun$");
getline(&buf, &bufsize, stdin);
printf("%s: No such file or directory\n", argv[0]);
}
return (0);
}
