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

int _getppid(char **args, int *status_for_exit);
int set_env_var(char **args);

int unset_env_var(char **args);
void d_exit(char **args);

void _env(char **envp);
int command_exists(char *command);

int get_loc(char *arg, char **args, char **env);
char *loc(char *path, char *arg, char **args, char **env);

int fork_cmd(char **args, char **env, char *p_name, int cmd_count);
int handle_cmd_sep(char *lineptr, char **envp, char *p_name, int c, int *exit);

int wait_status(int status);



#endif