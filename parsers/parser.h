#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define WRITE_END 1
#define READ_END 0


#include "../utils/utils.h"
#include "../executor/executor.h"
#include "../cmd/cmd.h"
#include "../shell.h"


void handle_pipe_commands(char *lineptr, shellInfo *shell);
char *fix_newline(char *str);
void rem_quotes(char *str);
void handle_cmd_b4pipe(int write_fd, char *cmd, shellInfo *shell);
void exec_cmd4_pipe(int inputed_fd, char *cmd, shellInfo *shell);
void exec_pipe_cmd(char *cmd, shellInfo *shell);
int pipe_execute(char **cmd1, char **cmd2, shellInfo *shell);
int redirection_execute(char **cmd, char *file, int type, shellInfo *shell);
int pipes_redirection(char *argv[], int argc, shellInfo *shell);
void read_input(char **argv, shellInfo shell);


int logical_op(char *lineptr, shellInfo *shell);
int logical_or(char *lineptr, shellInfo *shell);
int logical_co(char *lineptr, shellInfo *shell);
int execute_log_command(char *command, shellInfo *shell);

char *e_space(char *str);
char *_strtok(char *str, const char *delim);
char *fix_newline(char *str);
char *new_line(char *str);
char *_getline(void);
void rem_quotes(char *str);
void free_em(char **cmd, int count);

#endif