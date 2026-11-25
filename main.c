#include "main.h"
/**
 * prompt - prints the prompt to stdout
 * CWD is printed to the prompt, if available, otherwise a default prompt is used.
 * @cwd: current working directory
 * @base: base name of the current working directory
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
		printf(PROMPT);
		free(cwd);
	}
	else
	{
		printf(PROMPT);
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
	int fo_s;

	shellInfo shell;

	shell.envp = envp;
	shell.program_name = argv[0];
	shell.cmd_count = 0;
	shell.exit_status = 0;
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
				printf("\n");
				free(lineptr);
				break;
			}
			else
			{
				shell.cmd_count++;
				handle_cmd_sep(lineptr, &shell);
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
			read_input(argv, shell);
		}
	}
	return (0);
}

