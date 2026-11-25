#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#define WRITE_END 1
#define READ_END 0

#include "../utils/utils.h"
#include "../parsers/parser.h"
#include "../cmd/cmd.h"
#include "../shell.h"

int _getppid(char **args, shellInfo *shell);
int set_env_var(char **args);

int unset_env_var(char **args);
void d_exit(char **args);

void _env(shellInfo *shell);
int command_exists(char *command);

int get_loc(char *arg, char **args, shellInfo *shell);
char *loc(char *path, char *arg, char **args, shellInfo *shell);

int fork_cmd(char **args, shellInfo *shell);
int handle_cmd_sep(char *lineptr, shellInfo *shell);

int wait_status(int status);



#endif