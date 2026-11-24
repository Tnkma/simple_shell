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

int fork_cmd(char **args, char **env, char *p_name, int cmd_count)
{
	pid_t chpro;
	int status = 0, status_for_exit;


	if (command_exists(*args))
	{
		chpro = fork();
		if (chpro == -1)
		{
			perror("forking error");
		}
		else if (chpro == 0)
		{
			get_loc(args[0], args, env);
			perror("failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			do {

				waitpid(chpro, &status, WUNTRACED);
				status_for_exit = wait_status(status);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n", p_name, cmd_count, args[0]);
		status_for_exit = 127;
	}
	return (status_for_exit);
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

int handle_cmd_sep(char *lineptr, char **envp, char *p_name, int c, int *exit)
{
	char *delim = " \n\t\n\a", *args[100], *cmd, *token;
	int i = 0;

	if (strstr(lineptr, "&&"))
	{
		logical_op(lineptr, envp);
		return (*exit); }
	else if (strstr(lineptr, "||"))
	{
		logical_or(lineptr, envp);
		return (*exit); }
	else if (strstr(lineptr, ";"))
	{
		logical_co(lineptr, envp);
		return (*exit);
	}
	else if (strchr(lineptr, '|') || strchr(lineptr, '>') || strchr(lineptr, '<'))
	{
		handle_pipe_commands(lineptr, envp);
		return (*exit);
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
		if (built_cmd(args, envp, exit))
		{
			free(cmd);
			return (*exit); }
		*exit = fork_cmd(args, envp, p_name, c);
	}
	free(cmd);
	cmd = NULL;
	return (*exit);
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

