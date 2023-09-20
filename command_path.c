#include "main.h"

/**
 * loc - locate the path
 * @path: the direction of the string
 * @arg: the argument
 * @args: still the arguments
 * @env: the evn variable
 *
 * Return: Always 0 for sucess
 */

char *loc(char *path, char *arg, char **args, char **env)
{
	char *path_copy, *path_token, *file;
	char *delima = ":";

	path_copy = _strdup(path);
	/*copy path out before tokonizer*/
	file = malloc(_strlen(path_copy) + _strlen(arg) + 2);
	if (!file)
	{
		perror("failed to allocate");
		free(path_copy);
		return (NULL);
	}
	path_token = _strtok(path_copy, delima);
	while (path_token != NULL)
	{
		_strcpy(file, path_token);
		_strcat(file, "/");
		_strcat(file, arg);
		_strcat(file, "\0");
		if (access(file, X_OK) == 0)
		{
			execve(file, args, env);
			perror("execve");
			free(path_copy);
			free(file);
		}
		path_token = _strtok(NULL, delima);
	}
	free(file);
	free(path_copy);
	return (NULL);
}

/**
 * get_loc - calls out the path
 * @arg: the argument to find the path
 * @args: the argument
 * @env: the env
 *
 * Return: void since were void
 */

int get_loc(char *arg, char **args, char **env)
{
	char *p_aths;

	if (access(arg, X_OK) == 0)
	{
		if (execve(arg, args, env) == -1)
		{
			return (2);
		}
		else
		{
			return (0);
		}
		perror("execve error");
		exit(EXIT_FAILURE);
	}
	else
	{
		p_aths = getenv("PATH");
		if (p_aths)
		{
			loc(p_aths, arg, args, env);
			perror("command not found");
			return (-1);
		}
		return (-1);
	}
}
