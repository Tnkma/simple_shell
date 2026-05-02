#include "main.h"
/**
 * prompt - prints the prompt to stdout
 *
 *
 * Return: void since were void
 */
void prompt(void)
{
	char *cwd = getcwd(NULL, 0);
	char *base;

	if (cwd)
	{
		base = strrchr(cwd, '/');
		if (base && *(base + 1))
			base++;
		else
			base = cwd;

		_print(base);
		_print(" $ ");
		free(cwd);
	}
	else
	{
		_print("$ ");
	}

	fflush(stdout);
}

/**
 * Welcome message to display 
 */
void welcome_msg(void)
{
	char *msg =
	"Welcome to MyShell!\n"
	"You can run commands just like a normal shell.\n\n"
	"Modes available:\n"
	"  - Interactive mode: type commands and press Enter\n"
	"  - Non-interactive mode: pipe or redirect input\n\n"
	"Examples:\n"
	"  ls -l\n"
	"  echo Hello\n"
	"  cat file.txt\n\n"
	"Press Ctrl+D to exit.\n"
	"--------------------------------------------------\n";

	_print(msg);
}
/**
 * main - the main function that calls in other functions
 * @argc: holds the number of argument
 * @argv: the argument passed through the command line
 * @envp: the environmental variables
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
		welcome_msg();

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
		lineptr = NULL;
		free(lineptr);
		/*lineptr = NULL;*/
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

