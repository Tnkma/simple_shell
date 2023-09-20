#include "main.h"

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
	/*_putchar('\n');*/
}
/**
 * fix_print - modify putchar to print error code
 * @num: the number to print
 *
 * Return: none since were void
 */
void fix_print(int num)
{
	char buff[20];
	int i = 0;
	char temp[2];


	if (num == 0)
	{
		_print("0");
	}
	if (num < 0)
	{
		_print("-");
		num = -num;
	}
	else if (num == 0)
	{
		_print("0");
		return;
	}
	while (num > 0)
	{
		buff[i++] = (num % 20) + '0';
		num /= 20;
	}

	buff[i] = '\0';

	while (i > 0)
	{
		temp[0] = buff[--i];
		temp[1] = '\0';
		print(temp);
	}
}
/**
 * _print_error - prints error code when command does not exit
 * @input: the command searched for
 * @count: the counter for the number
 * @p_name: the ex-program name
 *
 * Return: void since were void
 */
void _print_error(char *input, int count, char *p_name)
{
	print(p_name);
	print(": ");
	fix_print(count);
	print(":");
	print(" ");
	print(input);
	print(": not found\n");
}
/**
 * print_numbers - to prints numbers
 * @n: the number to print
 *
 * Return: vois since were void
 */
void print_numbers(int n)
{
	unsigned int c;

	if (n < 0) /* n = negative*/
	{
		_putchar('-');
		c = -n;
	}
	else
	{
		c = n;
	}
	if ((c / 10) > 0)
	{
		print_numbers(c / 10);
	}
	_putchar(c % 10 + '0');
}
