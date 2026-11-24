#include "cmd.h"

/**
 * change_directory - changes the directory
 * @args: the argument to change
 *
 * Return: void since were void
 */

int change_directory(char **args)
{
	char *old_dir = getcwd(NULL, 0);
	char *new_dir;
	char *directory = args[1];
	char *home = getenv("HOME");
	char *oldpwd = getenv("OLDPWD");

	if (!old_dir)
	{
		perror("getcwd");
		return (1);
	}

	/* Handle: cd or cd ~ */
	if (!directory || _strcmp(directory, "~") == 0)
	{
		if (!home)
		{
			_print("cd: HOME not set\n");
			free(old_dir);
			return (1);
		}
		if (chdir(home) != 0)
		{
			perror("cd");
			free(old_dir);
			return (1);
		}
	}

	/* Handle: cd - */
	else if (_strcmp(directory, "-") == 0)
	{
		if (!oldpwd)
		{
			_print("cd: OLDPWD not set\n");
			free(old_dir);
			return (1);
		}
		if (chdir(oldpwd) != 0)
		{
			perror("cd");
			free(old_dir);
			return (1);
		}
		_print(oldpwd);
		_print("\n");
	}

	/* Handle normal directory */
	else
	{
		if (chdir(directory) != 0)
		{
			perror("cd");
			free(old_dir);
			return (1);
		}
	}

	/* Get new directory AFTER chdir */
	new_dir = getcwd(NULL, 0);
	if (!new_dir)
	{
		perror("getcwd");
		free(old_dir);
		return (1);
	}

	setenv("OLDPWD", old_dir, 1);
	setenv("PWD", new_dir, 1);

	free(old_dir);
	free(new_dir);

	return (0);
}
