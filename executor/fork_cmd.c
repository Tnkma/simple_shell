#include "executor.h"

/**
 * fork_cmd - fork the child process
 * @args: the arguments
 * @env: the env var
 * @p_name: for print_error
 * @cmd_count: command count
 *
 * Return: void since were void
 */

int fork_cmd(char **args, shellInfo *shell)
{
	pid_t chpro;
	int status = 0;


	if (command_exists(*args))
	{
		chpro = fork();
		if (chpro == -1)
		{
			perror("forking error");
		}
		else if (chpro == 0)
		{
			get_loc(args[0], args, shell);
			perror("failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			do {

				waitpid(chpro, &status, WUNTRACED);
				shell->exit_status = wait_status(status);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n", shell->program_name, shell->cmd_count, args[0]);
		shell->exit_status = 127;
	}
	return (shell->exit_status);
}

/**
 * handle_cmd_sep - handles command separation and executions of the command
 * @lineptr: the pointer to the arguments
 * @envp: the environmental varible
 * @p_name: the progam name to print error
 * @c: count of thhe program
 * @exit: exit status
 *
 * Return: void since were void.
 */

int handle_cmd_sep(char *lineptr, shellInfo *shell)
{
	char *delim = " \n\t\n\a", *args[100], *cmd, *token;
	int i = 0;

	if (strstr(lineptr, "&&"))
	{
		logical_op(lineptr, shell);
		return (shell->exit_status); 
	}
	else if (strstr(lineptr, "||"))
	{
		logical_or(lineptr, shell);
		return (shell->exit_status);
	 }
	else if (strstr(lineptr, ";"))
	{
		logical_co(lineptr, shell);
		return (shell->exit_status);
	}
	else if (strchr(lineptr, '|') || strchr(lineptr, '>') || strchr(lineptr, '<'))
	{
		handle_pipe_commands(lineptr, shell);
		return (shell->exit_status);
	}

	cmd = _strdup(lineptr);
	token = _strtok(cmd, delim);
	while (token && i < 100)
	{
		if (token[0] == '#')
		{
			break;
		}
		rem_quotes(token);
		args[i++] = (token);
		token = _strtok(NULL, delim); }
	args[i] = NULL;
	if (i > 0)
	{
		if (built_cmd(args, shell))
		{
			free(cmd);
			return (shell->exit_status); }
		shell->exit_status = fork_cmd(args, shell);
	}
	free(cmd);
	cmd = NULL;
	return (shell->exit_status);
}
/**
 * wait_status - different status for wait
 * @status: the status
 *
 * Return: Always 0 for success
 */
int wait_status(int status)
{
	int exit_status = WEXITSTATUS(status);

	switch (exit_status)
	{
		case 0:
		{
			return (0);
		}
		case 2:
		{
			return (2);
		}
		case 127:
		{
			return (127);
		}
		default:
		{
			return (exit_status);
		}
	}
}

