#include "executor.h"

/**
 * set_env_var - sets the enviromental var
 * @args: the argument to set
 *
 * Return: void since were void
 */

int set_env_var(char **args)
{
	if (!args[1] || !args[2])
	{
		_print("Usage: setenv VAR_NAME VALUE");
		return (1);
	}
	if (args[3])
	{
		_print("Error: too many arguments. Usage: setenv VAR_NAME VALUE");
		return (1);
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
		return (1);
	}
	return (0);
}
/**
 * unset_env_var - unset the enviromental varible
 * @args: the argument to unset
 *
 * Return: void since were void
 */

int unset_env_var(char **args)
{
	if (!args[1])
	{
		_print("Error: usage unsetenv VAR_NAME\n");
		return (1);
	}
	if (args[2])
	{
		_print("Error: Too many arguments. Usage: unsetenv VAR_NAME\n");
		return (1);
	}
	if (unsetenv(args[1]) != 0)
	{
		perror("Error unsetting enviroment variable");
		return (1);
	}
	return (0);
}
/**
 * d_exit - the exit function
 * @args: the argument
 * @status: the imported status
 * @p_name: the pathname
 * @count: the count of the commands
 *
 * Return: void since were void
 */

void d_exit(char **args)
{
	int store_inputted_num = EXIT_FAILURE;

	if (args[1])
	{
		store_inputted_num = _atoi(args[1]);
	}
	exit(store_inputted_num);
}
/**
 * _env - prints out the env command
 * @envp: the argument for env
 *
 * Return: void dince were void
 */

void _env(char **envp)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		_print(envp[i]);
		_print("\n");
	}
}
