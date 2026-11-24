#include "executor.h"

/**
 * _getppid - prints the getppid of the program
 * @args: the command
 * @status_for_exit: the number to print
 *
 * Return: Always 0 for success
 */
int _getppid(char **args, int *status_for_exit)
{
	char *path;
	unsigned int getcurrentid = getpid();

	if (!args[1])
	{
		return (0);
	}
	if (strncmp(args[1], "$?", 2) == 0)
	{
		printf("%d", *status_for_exit);
		_print("\n");
		return (1);
	}
	else if (strncmp(args[1], "$$", 2) == 0)
	{
		printf("%d", getcurrentid);
		_print("\n");
		return (1);
	}
	else if (strncmp(args[1], "$PATH", 5) == 0)
	{
		path = getenv("PATH");
		_print(path);
		_print("\n");
		return (1);
	}
	return (0);
}