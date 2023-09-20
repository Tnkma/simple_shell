#include "main.h"

/**
 * change_directory - changes the directory
 * @args: the argument to change
 *
 * Return: void since were void
 */

void change_directory(char **args)
{
	char *n_dir = getcwd(NULL, 0), *oldpwd = getenv("OLDPWD");
	char *directory = args[1], *old_dir = getcwd(NULL, 0);

	if (!directory)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			free(old_dir);
			return; }
	}
	else if (_strcmp(directory, "-") == 0)
	{
		if (oldpwd)
		{
			if (chdir(oldpwd) != 0)
			{
				perror("cd");
				free(old_dir);
				return; }
			_print(oldpwd);
			_print("\n"); }
		else
		{
			_print("cd: OLDPWD not set\n");
			free(old_dir);
			return; }
	}
	else
	{
		if (chdir(directory) != 0)
		{
			perror("cd");
			free(old_dir);
			return; }
	}
	setenv("PWD", n_dir, 1);
	setenv("OLDPWD", old_dir, 1);
	free(old_dir);
	free(n_dir);
}


/**
 * set_env_var - sets the enviromental var
 * @args: the argument to set
 *
 * Return: void since were void
 */

void set_env_var(char **args)
{
	if (!args[1] || !args[2])
	{
		_print("Usage set to setenv VAR_NAME VALUE");
		return;
	}
	if (args[3])
	{
		_print("Eror: many argument");
		return;
	}
	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}
}
/**
 * unset_env_var - unset the enviromental varible
 * @args: the argument to unset
 *
 * Return: void since were void
 */

void unset_env_var(char **args)
{
	if (!args[1])
	{
		_print("Error: usuage unsetenv VAR_NAME\n");
		return;
	}
	if (args[2])
	{
		_print("Error: Too many argument. Usage: unsetenv VAR_NAME\n");
	}
	if (unsetenv(args[1]) != 0)
	{
		perror("Error unsetting enviroment variable");
	}
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

void d_exit(char **args, int *status, char *p_name, int count)
{
	int store_inputted_num;

	if (args[1])
	{
		store_inputted_num = _atoi(args[1]);

		if (store_inputted_num < 0 || store_inputted_num > 255)
		{
			print_exit_error(p_name, count, store_inputted_num);
			return;
		}
		*status = store_inputted_num;
	}
	exit(*status);
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
