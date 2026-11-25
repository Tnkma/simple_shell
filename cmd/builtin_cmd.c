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

int built_cmd(char **args, shellInfo *shell)
{
    char *command = args[0];

    if (_getppid(args, shell))
        return (1);

    if (_strcmp(command, "cd") == 0)
    {
        shell->exit_status = change_directory(args);
        return (1);
    }
    else if (_strcmp(command, "setenv") == 0)
    {
        shell->exit_status = set_env_var(args);
        return (1);
    }
    else if (_strcmp(command, "unsetenv") == 0)
    {
        shell->exit_status = unset_env_var(args);
        return (1);
    }
    else if (_strcmp(command, "env") == 0)
    {
        _env(shell);
        shell->exit_status = 0;
        return (1);
    }
    else if (_strcmp(command, "exit") == 0)
    {
        d_exit(args);
    }
    return (shell->exit_status);
}

