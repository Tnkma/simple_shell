#include "cmd.h"


/**
 * command_exists - check if command can be found
 * @command: the string to check
 *
 *
 * Return: Always 0 for success
 */
int command_exists(char *command)
{
	char *path = getenv("PATH");
	char *cmd_cpy;
	char cmd_path[256];
	char *p;
	int cf = 0;
	size_t t_length;

	if (!path)
	{
		return (0);
	}
	cmd_cpy = _strdup(path);
	
	if (!cmd_cpy)
	{
		free(cmd_cpy);
		return (0);
	}

	p = _strtok(cmd_cpy, ":");

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
		{
			free(cmd_cpy);
			return (1);
		}
		free(cmd_cpy);
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