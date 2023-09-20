#include "main.h"

/**
 * _strlen - the function to count the string
 * @s: the string to be counted
 *
 * Return: Always void
 */

int _strlen(char *s)
{
	/* A variable to count the string */
	int c;

	for (c = 0; s[c] != '\0'; c++)
	{

	}
	return (c);
}

/**
 * _strcpy - copies the string including the \0 char
 * @dest: destination of the string
 * @src: source of the string
 *
 * Return: a pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	char *start = dest;
	char *end = src;

	while (*end != '\0')
	{
		*start = *end;
		start++;
		end++;
	}
	*start = '\0';
	return (dest);
}

/**
 * _strcat - the function to write
 * @dest: destination string
 * @src: source string
 *
 * Return: Always a char pointer
 */

char *_strcat(char *dest, char *src)
{
	char *base_string = dest;
	char *source_string = src;

	while (*base_string != '\0')
	{
		base_string++;
	}
	while (*source_string != '\0')
	{
		*base_string = *source_string;
		base_string++;
		source_string++;
	}
	*base_string = '\0';
	return (dest);
}

/**
 * _strcmp - the function prototype
 * @s1: the first string
 * @s2: the second string
 *
 *
 * Return: Always int
 */

int _strcmp(char *s1, char *s2)
{
	char *am_first = s1;
	char *lasty = s2;

	if (!am_first || !lasty)
	{
		if (!am_first && !lasty)
		{
			return (0);
		}
		return (am_first ? 15 : -15);
	}
	/*first find the strings and then compare using ACSII*/
	while (*am_first != '\0' && *lasty != '\0')
	{
		if (*am_first != *lasty)
		{
			if (*am_first > *lasty)
			{
				return (15);
			}
			else if (*lasty > *am_first)
			{
				return (-15);
			}
		}
		am_first++;
		lasty++;
	}
	if (*am_first == '\0' && *lasty != '\0')
	{
		return (-15);
	}
	else if (*am_first != '\0' && *lasty == '\0')
	{
		return (15);
	}
	return (0);
}
