#include "main.h"

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
		_print_error(args[0], cmd_count, p_name);
		status_for_exit = 127;
	}
	return (status_for_exit);
}

/**
 * handle_cmd_sep - handles command separation
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
	cmd = _strdup(lineptr);
	token = _strtok(cmd, delim);
	while (token && i < 100)
	{
		if (token[0] == '#')
		{
			break; }
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

/**
 * command_exists - check if command can be found
 * @command: the string to check
 *
 *
 * Return: Always 0 for success
 */
size_t command_exists(char *command)
{
	char *path = getenv("PATH");
	char *cmd_cpy = _strdup(path);

	char *p = _strtok(cmd_cpy, ":");
	char cmd_path[256];
	int cf = 0;
	size_t t_length;

	if (strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
		{
			free(cmd_cpy);
			return (1);
		}
		free(cmd_cpy);
		return (0);
	}
	if (!cmd_cpy)
	{
		return (0);
	}


	while (p)
	{
		t_length = _strlen(p) + _strlen(command) + 2;
		if (t_length < sizeof(cmd_path))
		{
			snprintf(cmd_path, sizeof(cmd_path), "%s/%s", p, command);
			if (access(cmd_path, X_OK) == 0)
			{
				cf = 1;
				break;
			}
		}
		p = _strtok(NULL, ":");
	}
	free(cmd_cpy);
	return (cf);
}
