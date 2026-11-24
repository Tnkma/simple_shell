#include "cmd.h"

/**
 * built_cmd - A function to handle built in commands
 * @args: vector arrays passed in
 * @envp: second vector arrya pass in
 * @status_for_exit: exit staustus
 * @count: count of the commands
 *
 * Return: Always 0 for success
 */

int built_cmd(char **args, char **envp, int *status_for_exit)
{
    char *command = args[0];

    if (_getppid(args, status_for_exit))
        return (1);

    if (_strcmp(command, "cd") == 0)
    {
        *status_for_exit = change_directory(args);
        return (1);
    }
    else if (_strcmp(command, "setenv") == 0)
    {
        *status_for_exit = set_env_var(args);
        return (1);
    }
    else if (_strcmp(command, "unsetenv") == 0)
    {
        *status_for_exit = unset_env_var(args);
        return (1);
    }
    else if (_strcmp(command, "env") == 0)
    {
        _env(envp);
        *status_for_exit = 0;
        return (1);
    }
    else if (_strcmp(command, "exit") == 0)
    {
        d_exit(args);
    }
    return (*status_for_exit);
}

