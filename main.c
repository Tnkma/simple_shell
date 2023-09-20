#include "main.h"
/**
 * prompt - prints the promt
 *
 *
 * Return: void since were void
 */
void prompt(void)
{
	char *pr = "$ ";

	_print(pr);
	fflush(stdout);
}
/**
 * main - the main function
 * @argc: holds the number of argument
 * @argv: the argument passed
 * @envp: the environmental variable
 *
 * Return: Always 0 on success.
 */

int main(int argc, char **argv, char **envp)
{
	char *lineptr = NULL;
	int fo_s, cmd_count = 0;
	int exit_status = 0;

	fo_s = isatty(STDIN_FILENO);
	if (fo_s == 1)
	{

		while (1)
		{
			prompt();

			lineptr = _getline();
			if (lineptr == NULL) /*EOF detected*/
			{
				_print("\n");
				free(lineptr);
				break;
			}
			else
			{
				cmd_count++;
				handle_cmd_sep(lineptr, envp, argv[0], cmd_count, &exit_status);
			}
		}
		free(lineptr);
		lineptr = NULL;
	}
	else
	{
		if (argc < 2)
		{
			read_input(argv, envp);
		}
	}
	return (0);
}

