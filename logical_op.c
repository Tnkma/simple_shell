#include "main.h"

/**
 * execute_log_command - execute the logical command assigned from the logical operator functions
 * @command: the command to execute
 * @env: the enviromental variable
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
 * logical_AND_ops - executes && commands
 * @lineptr: the arguent from command_line
 * @env: enviromental avriable
 *
 *
 * Return: Always 0 for success
 */
int logical_op(char *lineptr, char **env)
{
	char *command, *token[100], *current_command;
	char *args[100], *tok;
	int exit_status = 0, i, j, cmd_count = 0, status, mem = 0;
	pid_t chpro;

	/* split by && */
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

		/* check for pipe or redirection BEFORE splitting */
		if (strchr(current_command, '|') || strchr(current_command, '>') || strchr(current_command, '<'))
		{
			j = 0;
			tok = _strtok(current_command, " \t\n");

			while (tok && j < 100)
			{
				args[j++] = tok;
				tok = _strtok(NULL, " \t\n");
			}
			args[j] = NULL;

			exit_status = pipes_redirection(args, j, env);

			/* stop if failed */
			if (exit_status != 0)
			{
				free_em(token, cmd_count);
				mem = 1;
				break;
			}
			continue;
		}

		/* NORMAL COMMAND PATH */
		j = 0;
		tok = _strtok(current_command, " \t\n");

		while (tok && j < 100)
		{
			args[j++] = tok;
			tok = _strtok(NULL, " \t\n");
		}
		args[j] = NULL;

		if (args[0] == NULL)
			continue;

		/* builtin */
		if (built_cmd(args, env, &exit_status))
		{
			continue;
		}

		/* external command */
		chpro = fork();
		if (chpro == 0)
		{
			if (get_loc(args[0], args, env) == -1)
				exit(EXIT_FAILURE);
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
				}
			}
		}
		else
		{
			perror("fork");
			free_em(token, cmd_count);
			return (1);
		}
	}

	if (!mem)
		free_em(token, cmd_count);

	return (exit_status);
}

/**
 * logical_OR_ops - executes || commands
 * @lineptr: the argument from command_line
 * @env: env variable
 *
 *
 * Return: Always 0 for success
 */
int logical_or(char *lineptr, char **env)
{
	char *command, *token[100], *current_command;
	char *args[100], *tok;
	int exit_status = 0, i, j, cmd_count = 0, status, mem = 0;
	pid_t chpro;

	/* split by || */
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
		/* check for pipe or redirection BEFORE splitting */
		if (strchr(current_command, '|') ||
			strchr(current_command, '>') ||
			strchr(current_command, '<'))
		{
			j = 0;
			tok = _strtok(current_command, " \t\n");

			while (tok && j < 100)
			{
				args[j++] = tok;
				tok = _strtok(NULL, " \t\n");
			}
			args[j] = NULL;

			exit_status = pipes_redirection(args, j, env);

			/* stop if failed */
			if (exit_status != 0)
			{
				free_em(token, cmd_count);
				mem = 1;
				break;
			}
			continue;
		}

		/* NORMAL COMMAND PATH */
		j = 0;
		tok = _strtok(current_command, " \t\n");

		while (tok && j < 100)
		{
			args[j++] = tok;
			tok = _strtok(NULL, " \t\n");
		}
		args[j] = NULL;

		if (args[0] == NULL)
			continue;

		/* builtin */
		if (built_cmd(args, env, &exit_status))
		{
			continue;
		}

		/* external command */
		chpro = fork();
		if (chpro == 0)
		{
			if (get_loc(args[0], args, env) == -1)
				exit(EXIT_FAILURE);
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
				}
			}
		}
		else
		{
			perror("fork");
			free_em(token, cmd_count);
			return (1);
		}
	}

	if (!mem)
		free_em(token, cmd_count);

	return (exit_status);
}

/**
 * logical_co - executes ; commands
 * @lineptr: the argument from command_line
	 * @env: env variable
 * Return: Always 0 for success
 */
int logical_co(char *lineptr, char **env)
{
	char *command, *token[100], *current_command;
	char *args[100], *tok;
	int exit_status = 0, i, j, cmd_count = 0, status, mem = 0;
	pid_t chpro;

	/* split by ; */
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

		/* check for pipe or redirection BEFORE splitting */
		if (strchr(current_command, '|') ||
			strchr(current_command, '>') ||
			strchr(current_command, '<'))
		{
			j = 0;
			tok = _strtok(current_command, " \t\n");

			while (tok && j < 100)
			{
				args[j++] = tok;
				tok = _strtok(NULL, " \t\n");
			}
			args[j] = NULL;

			exit_status = pipes_redirection(args, j, env);

			/* stop if failed */
			if (exit_status != 0)
			{
				free_em(token, cmd_count);
				mem = 1;
				break;
			}
			continue;
		}

		/* NORMAL COMMAND PATH */
		j = 0;
		tok = _strtok(current_command, " \t\n");

		while (tok && j < 100)
		{
			args[j++] = tok;
			tok = _strtok(NULL, " \t\n");
		}
		args[j] = NULL;

		if (args[0] == NULL)
			continue;

		/* builtin */
		if (built_cmd(args, env, &exit_status))
		{
			continue;
		}

		/* external command */
		chpro = fork();
		if (chpro == 0)
		{
			if (get_loc(args[0], args, env) == -1)
				exit(EXIT_FAILURE);
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
				}
			}
		}
		else
		{
			perror("fork");
			free_em(token, cmd_count);
			return (1);
		}
	}

	if (!mem)
		free_em(token, cmd_count);

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
