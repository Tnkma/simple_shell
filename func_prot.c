#include "main.h"

/**
 * _strdup - copies the string and returns the pointer
 * @str: the string to copy
 *
 * Return: Always 0 for sucess
 */

char *_strdup(const char *str)
{
	char *buffer;
	int i;
	int len = 0;


	/* Getting the length of the string*/
	while (str[len])

		len++;

	buffer = (char *)malloc(len + 1);
	/*use len to allocate memory + null*/

	if (buffer == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < len; i++)
	{
		buffer[i] = str[i];
		/*The string should be copied to buffer*/
	}

	/*Assign Null back buffer to close it */
	buffer[len] = '\0';

	return (buffer);
}

/**
 * _atoi - Entry point
 * @s: input
 * Return: Always 0 (Success)
 */
int _atoi(char *s)
{
	unsigned int num = 0;
	int sign = 1;


	do {
		if (*s == '-')
			sign *= -1;
		else if
			(*s >= '0' && *s <= '9')
				num = (num * 10) + (*s - '0');
		else if
			(num > 0)
				break;
	} while (*s++);
	return (num * sign);
}
#include "main.h"

/**
 * _strchr - finds a certain character and prints from there
 * @s: the memory to search
 * @c: the charcter to search
 *
 * Return: A pointer to the address of the memory
 */

char *_strchr(char *s, char c)
{
	/* declare a variable to ilterate the characaters*/
	int i;

	int length = strlen(s);

	for (i = 0; i <= length; i++)
	{
		if (s[i] == c)
		{
			return (&s[i]);
		}
	}
	return (NULL);
}
