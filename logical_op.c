#include "main.h"

/**
 * execute_log_command - execute the command
 * @command: the command to execute
 * @env: the enviromental avriable
 *
 * Return: Always 0 for success
 */
int execute_log_command(char *command, char **env)
{
	const int MAX_ARGS = 64;
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *token;
	int count = 0, ret_value;

	token = _strtok(command, " ");

	while (token != NULL && count < MAX_ARGS - 1)
	{
		args[count++] = token;
		token = _strtok(NULL, " ");
	}
	args[count] = NULL;

	ret_value = get_loc(args[0], args, env);
	if (ret_value == -1)
	{
		free(args);
		exit(EXIT_FAILURE);
	}
	free(args);
	return (0);
}

/**
 * logical_op - executes && commands
 * @lineptr: the arguent from command_line
 * @env: enviromental avriable
 *
 *
 * Return: Always 0 for success
 */
int logical_op(char *lineptr, char **env)
{
	char *command, *token[100], *current_command;
	int exit_status = 0, i, cmd_count = 0, status, mem = 0;
	pid_t chpro;

	command = _strtok(lineptr, "&&");
	while (command && cmd_count < 100)
	{
		token[cmd_count++] = _strdup(command);
		command = _strtok(NULL, "&&");
	}
	token[cmd_count] = NULL;
	for (i = 0; i < cmd_count; i++)
	{
		current_command = token[i];
		status = 0;
		chpro = fork();
		if (chpro == 0)
		{
			execute_log_command(current_command, env);
		}
		else if (chpro > 0)
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				exit_status = wait_status(status);
				if (exit_status != 0)
				{
					free_em(token, cmd_count);
					mem = 1;
					break;
					return (exit_status);
				}
			}
		}
	}
	if (!mem)
	{
		free_em(token, cmd_count); }
	return (exit_status);
}

/**
 * logical_or - executes && commands
 * @lineptr: the arguent from command_line
 * @env: env variable
 *
 *
 * Return: Always 0 for success
 */
int logical_or(char *lineptr, char **env)
{
	char *command, *token[100], *current_command;
	int exit_status = 0, i, cmd_count = 0, status, mem = 0;
	pid_t chpro;

	command = _strtok(lineptr, "||");
	while (command && cmd_count < 100)
	{
		token[cmd_count++] = _strdup(command);
		command = _strtok(NULL, "||");
	}
	token[cmd_count] = NULL;
	for (i = 0; i < cmd_count; i++)
	{
		current_command = token[i];
		status = 0;
		chpro = fork();
		if (chpro == 0)
		{
			execute_log_command(current_command, env);
		}
		else if (chpro > 0)
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				exit_status = wait_status(status);
				if (exit_status == 0)
				{
					free_em(token, cmd_count);
					mem = 1;
					break;
					return (exit_status);
				}
			}
		}
	}
	if (!mem)
	{
		free_em(token, cmd_count); }
	return (exit_status);
}

/**
 * logical_co - executes && commands
 * @lineptr: the arguent from command_line
 * @env: env variable
 *
 *
 * Return: Always 0 for success
 */
int logical_co(char *lineptr, char **env)
{
	char *cmd_copy, *command, *token[100], *current_command;
	int exit_status = 0, i, cmd_count = 0, status;
	pid_t chpro;

	cmd_copy = _strdup(lineptr);
	command = _strtok(lineptr, ";");
	while (command && cmd_count < 100)
	{
		token[cmd_count++] = _strdup(command);
		command = _strtok(NULL, ";");
	}
	token[cmd_count] = NULL;
	for (i = 0; i < cmd_count; i++)
	{
		current_command = token[i];
		status = 0;

		chpro = fork();
		if (chpro == 0)
		{
			execute_log_command(current_command, env);
		}
		else if (chpro > 0)
		{
			wait(&status);
			if (WIFEXITED(status))
			{
				exit_status = wait_status(status);
			}
		}
		else
		{
			perror("could not fork");
			exit(EXIT_FAILURE);
		}
	}
	free_em(token, cmd_count);
	free(cmd_copy);
	return (exit_status);
}
/**
 * free_em - frees the token
 * @cmd: the command to free
 * @count: count of the comand
 *
 * Return: void since were void
 */
void free_em(char **cmd, int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		free(cmd[i]);
	}
}
