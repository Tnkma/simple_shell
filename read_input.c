#include "main.h"

/**
 * read_input - reads input from stdin
 * @argv: the arguments to be read
 * @envp: the environ var
 *
 * Return: void since were void
 */

void read_input(char **argv, char **envp)
{
	char *lineptr = NULL;
	int cn = 0, exit_status = 0;

	while (1)
	{
		lineptr = _getline();
		if (lineptr == NULL)
		{
			free(lineptr);
			break;
		}

		cn++;
		handle_cmd_sep(lineptr, envp, argv[0], cn, &exit_status);
		free(lineptr);
		lineptr = NULL;
	}
}
/**
 * fix_newline - fixes the new line on the string
 * @str: the string to trim the newline
 *
 * Return: the trimed string
 */

char *fix_newline(char *str)
{
	int start_of = 0, end_of, i, len;
	char *fixed_str;

	len = _strlen(str);

	while (str[start_of] == ' ' || str[start_of] == '\n')
		start_of++;
	end_of = len - 1;
	while (end_of > start_of && (str[end_of] == ' ' || str[end_of] == '\n'))
		end_of--;

	fixed_str = malloc(end_of - start_of + 2);
	if (!fixed_str)
	{
		return (NULL);
	}
	for (i = 0; start_of <= end_of; start_of++, i++)
	{
		fixed_str[i] = str[start_of];
	}

	fixed_str[i] = '\0';
	return (fixed_str);
}
