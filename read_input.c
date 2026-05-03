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
 * @str: the string that needs to be trim the newline
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
/**
 * handle_pipe_commands - handles pipe commands
 * @lineptr: the pointer to the line
 * @envp: the environmental variable
 *
 * Return: void since were void
 */

void handle_pipe_commands(char *lineptr, char **envp)
{
	char *command_copy, *single_command;
	char *args[100];
	char *token;
	int i;

	command_copy = _strdup(lineptr);
	if (!command_copy)
		return;

	single_command = _strtok(command_copy, ";");

	while (single_command)
	{
		i = 0;
		token = _strtok(single_command, " \t\n");

		while (token && i < 100)
		{
			args[i++] = token;
			token = _strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		if (i > 0)
			pipes_redirection(args, i, envp);

		single_command = _strtok(NULL, ";");
	}

	free(command_copy);
}
/**
 * pipes_redirection - handles both pipes and redirections
 * @argv: the arguments of the command
 * @argc: the count of the arguments
 * @env: the env variable
 *
 * Return: Always 0 for success
 */
int pipes_redirection(char *argv[], int argc, char **env)
{
	char *command1[100], *command2[100];
	int i, split = 0;
	int flag_pipe = 0, flag_redirection = 0;
	char type_red[3];

	int c1 = 0, c2 = 0;

	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "|") == 0)
		{
			flag_pipe = 1;
			split = 1;
			continue;
		}
		else if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], "<") == 0 || strcmp(argv[i], ">>") == 0)
		{
			flag_redirection = 1;
			strcpy(type_red, argv[i]);
			split = 1;
			continue;
		}

		if (!split)
			command1[c1++] = argv[i];
		else
			command2[c2++] = argv[i];
	}

	command1[c1] = NULL;
	command2[c2] = NULL;

	if (flag_pipe)
	{
		return pipe_execute(command1, command2, env);
	}

	if (flag_redirection)
	{
		int type;

		if (strcmp(type_red, ">") == 0)
			type = 0;
		else if (strcmp(type_red, ">>") == 0)
			type = 1;
		else
			type = 2; /* < */

		return redirection_execute(command1, command2[0], type, env);
	}

	return -1;
}
/**
 * pipe_execute - executes pipe commands
 * @cmd1: the first command
 * @cmd2: the second command
 * @env: the env variable
 *
 * Return: Always 0 for success
 */
int pipe_execute(char **cmd1, char **cmd2, char **env)
{
	int fd[2];
	pid_t pid1, pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return -1;
	}

	if (!command_exists(cmd1[0]) || !command_exists(cmd2[0]))
	{
		_print("Error: Command not found.\n");
		return -1;
	}

	pid1 = fork();
	if (pid1 == 0)
	{
		/* First command */
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);




		get_loc(cmd1[0], cmd1, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}

	if (!command_exists(cmd1[0]) || !command_exists(cmd2[0]))
	{
		_print("Error: Command not found.\n");
		return -1;
	}


	pid2 = fork();
	if (pid2 == 0)
	{
		/* Second command */
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);

		get_loc(cmd2[0], cmd2, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}

	/* Parent */
	close(fd[0]);
	close(fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}
/**
 * redirection_execute - executes redirection commands
 * @cmd: the command to execute
 * @file: the file to redirect to
 * @type: the type of redirection
 * @env: the environment variables
 *
 * Return: Always 0 for success
 */

int redirection_execute(char **cmd, char *file, int type, char **env)
{
	int fd;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (type == 0) /* > */
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (type == 1) /* >> */
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else /* < */
			fd = open(file, O_RDONLY);

		if (fd < 0)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}

		if (type == 2)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);

		close(fd);

		get_loc(cmd[0], cmd, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}

	waitpid(pid, NULL, 0);
	return 0;
}