#include "main.h"

/**
 * change_directory - changes the directory
 * @args: the argument to change
 *
 * Return: void since were void
 */

void change_directory(char **args)
{
	char *old_dir = getcwd(NULL, 0);
	char *new_dir;
	char *directory = args[1];
	char *home = getenv("HOME");
	char *oldpwd = getenv("OLDPWD");

	if (!old_dir)
	{
		perror("getcwd");
		return;
	}

	/* Handle: cd or cd ~ */
	if (!directory || _strcmp(directory, "~") == 0)
	{
		if (!home)
		{
			_print("cd: HOME not set\n");
			free(old_dir);
			return;
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			free(old_dir);
			return;
		}
	}

	/* Handle: cd - */
	else if (_strcmp(directory, "-") == 0)
	{
		if (!oldpwd)
		{
			_print("cd: OLDPWD not set\n");
			free(old_dir);
			return;
		}
		if (chdir(oldpwd) != 0)
		{
			perror("cd");
			free(old_dir);
			return;
		}
		_print(oldpwd);
		_print("\n");
	}

	/* Handle normal directory (including .. automatically) */
	else
	{
		if (chdir(directory) != 0)
		{
			perror("cd");
			free(old_dir);
			return;
		}
	}

	/* Get new directory AFTER chdir */
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		perror("getcwd");
		free(old_dir);
		return;
	}

	setenv("OLDPWD", old_dir, 1);
	setenv("PWD", new_dir, 1);

	free(old_dir);
	free(new_dir);
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
		_print("Usage: setenv VAR_NAME VALUE");
		return;
	}
	if (args[3])
	{
		_print("Error: too many arguments. Usage: setenv VAR_NAME VALUE");
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
		_print("Error: usage unsetenv VAR_NAME\n");
		return;
	}
	if (args[2])
	{
		_print("Error: Too many arguments. Usage: unsetenv VAR_NAME\n");
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
