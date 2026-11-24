#include "utils.h"

/**
 * _putchar - prints the string
 * @c: the character to print
 *
 * Return: Always 0 for success
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _print - since _putchar prints one c, print plenty
 * @str: the string to print
 *
 * Return: void since were void
 */
void _print(const char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);

		str++;
	}
}

/**
 * print_int - modify putchar to print error code
 * Basically, takes an integer and prints it to the standard output.
 * @num: the number to print
 *
 * Return: none since were void
 */
void print_int(int num)
{
	unsigned int c;

	if (num < 0) /* num = negative*/
	{
		_putchar('-');
		c = -num;
	}
	else
	{
		c = num;
	}
	if ((c / 10) > 0)
	{
		print_int(c / 10);
	}
	_putchar(c % 10 + '0');
}

/**
 * print_exit_error - prints error code when command does not exit
 * @input: the command searched for
 * @count: the counter for the number
 * @p_name: the ex-program name
 *
 * Return: void since were void
 */
void print_exit_error(char *input, int count, char *p_name)
{
	_print(p_name);
	_print(": ");
	print_int(count);
	_print(":");
	_print(" ");
	_print(input);
	_print(": not found\n");
}

/**
 * print_echo - implement the echo command
 * @cmd: the command to print
 *
 * Return: Always 0 for sucess
 */

int print_echo(char **cmd)
{
	int i = 1;

	while (cmd[i])
	{
		if (i > 1)
		{
			_print(" ");
			_print(cmd[i]);
			i++;
		}
	}

	_print("\n");

	return (1);
}
