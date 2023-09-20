#include "main.h"

/**
 * new_line - handles newline character
 * @str: the string
 *
 * Return: void since were void
 */
char *new_line(char *str)
{
	free(str);
	return ("\0");
}
/**
 * e_space - handles extra space
 * @str: the inputed strings
 *
 * Return: the function to remove the string
 */
char *e_space(char *str)
{
	int j, m = 0;
	char *buff;

	buff = malloc(sizeof(char) * (_strlen(str) + 1));
	if (buff == NULL)
	{
		return (NULL);
	}
	for (j = 0; str[j] == ' '; j++)
		;
	for (; str[j + 1] != '\0'; j++)
	{
		buff[m] = str[j];
		m++;
	}
	buff[m] = '\0';
	if (buff[0] == '\0' || buff[0] == '#')
	{
		free(buff);
		return ("\0");
	}
	return (buff);
}

/**
 * _getline - getline prototype
 *
 * Return: the inputed string
 */

char *_getline(void)
{
	int i, re, bufsize = 1024;
	char ch = 0, *buf, *modi_str, *fixed;

	buf = malloc(bufsize);
	if (buf == NULL)
	{
		return (NULL);
	}
	for (i = 0; ch != EOF && ch != '\n'; i++)
	{
		fflush(stdin);
		re = read(STDIN_FILENO, &ch, 1);
		if (re == 0)
		{
			free(buf);
			return (NULL);
		}
		buf[i] = ch;
		if (buf[0] == '\n')
			return (new_line(buf));
		if (i >= bufsize)
		{
			buf = realloc(buf, (bufsize + 2));
			if (buf == NULL)
			{
				return (NULL);
			}
		}
	}
	buf[i] = '\0';
	modi_str = e_space(buf);
	if (buf)
	{
		free(buf);
	}
	fixed = fix_newline(modi_str);
	if (modi_str)
		free(modi_str);
	return (fixed);
}
/**
 * _strtok - split the string based on delim
 * @str: the string to split
 * @delim: the delim to put
 *
 * Return: a pointer contain the tokonized string
 */

char *_strtok(char *str, const char *delim)
{
	static char *dum;
	char *end_str;

	if (str == NULL)
	{
		str = dum;
		if (str == NULL)
		{
			return (NULL);
		}
	}
	/*move str to first non_delim character*/
	while (*str && strchr(delim, *str))
		str++;
	if (*str == '\0')
	{
		dum = NULL;
		return (NULL);
	}
	/*find the end of this token*/
	end_str = str;
	while (*end_str && !strchr(delim, *end_str))
		end_str++;
	/*null_terminate any delim found*/
	if (*end_str)
	{
		*end_str = '\0';
		dum = end_str + 1;
	}
	else
	{
		dum = NULL;
	}
	return (str);
}

/**
 * rem_quotes - removes quotes
 * @str: the input
 *
 * Return: void since were void
 */

void rem_quotes(char *str)
{
	int len;

	len = _strlen(str);

	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
	{
		memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
}
