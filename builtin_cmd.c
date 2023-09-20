#include "main.h"

/**
 * built_cmd - A function to handle built in commands
 * @args: vector arrays passed in
 * @envp: second vector arrya pass in
 * @status_for_exit: exit staustus
 * @count: count of the commands
 *
 * Return: Always 0 for success
 */

int built_cmd(char **args, char **envp, int *status_for_exit, int count)
{

	char *command = args[0];

	if (_getppid(args, status_for_exit))
	{
		return (1);
	}
	if (_strcmp(command, "cd") == 0)
	{
		change_directory(args);
		return (1);
	}

	else if (_strcmp(command, "setenv") == 0)
	{
		set_env_var(args);
		return (1);
	}
	else if (_strcmp(command, "unsetenv") == 0)
	{
		unset_env_var(args);
		return (1);
	}
	else if (_strcmp(command, "exit") == 0)
	{
		d_exit(args, status_for_exit, args[0], count);
	}
	else if (_strcmp(command, "env") == 0)
	{
		_env(envp);
		return (1);
	}


	return (*status_for_exit);
}

/**
 * _getppid - prints the getppid of the program
 * @args: the command
 * @status_for_exit: the number to print
 *
 * Return: Always 0 for success
 */
int _getppid(char **args, int *status_for_exit)
{
	char *path;
	unsigned int getp = getpid();

	if (!args[1])
	{
		return (0);
	}
	if (strncmp(args[1], "$?", 2) == 0)
	{
		print_numbers(*status_for_exit);
		_print("\n");
		return (1);
	}
	else if (strncmp(args[1], "$$", 2) == 0)
	{
		print_numbers(getp);
		_print("\n");
		return (1);
	}
	else if (strncmp(args[1], "$PATH", 5) == 0)
	{
		path = getenv("PATH");
		_print(path);
		_print("\n");
		return (1);
	}
	return (0);
}
/**
 * print_exit_error - prints the exit error
 * @p_name: the command name
 * @count: count of the commands
 * @num: the number
 *
 * Return: void since were void
 */
void print_exit_error(char *p_name, int count, int num)
{
	_print(p_name);
	_print(": ");
	fix_print(count);
	_print(": exit: illegal number: ");
	print_numbers(num);
	_print("\n");
}
/**
 * print_echo - implement the echo command
 * @cmd: the command to print
 *
 * Return: Always 0 for sucess
 */

int print_echo(char **cmd)
{
	int i = 1;

	while (cmd[i])
	{
		if (i > 1)
		{
			_print(" ");
			_print(cmd[i]);
			i++;
		}
	}

	_print("\n");

	return (1);
}
