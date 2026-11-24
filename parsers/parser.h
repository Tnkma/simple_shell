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


void handle_pipe_commands(char *lineptr, char **envp);
char *fix_newline(char *str);
void rem_quotes(char *str);
void handle_cmd_b4pipe(int write_fd, char *cmd, char **envp);
void exec_cmd4_pipe(int inputed_fd, char *cmd, char **envp);
void exec_pipe_cmd(char *cmd, char **envp);
int pipe_execute(char **cmd1, char **cmd2, char **env);
int redirection_execute(char **cmd, char *file, int type, char **env);
int pipes_redirection(char *argv[], int argc, char **env);
void read_input(char **argv, char **envp);


int logical_op(char *lineptr, char **env);
int logical_or(char *lineptr, char **env);
int logical_co(char *lineptr, char **env);
int execute_log_command(char *command, char **env);

char *e_space(char *str);
char *_strtok(char *str, const char *delim);
char *fix_newline(char *str);
char *new_line(char *str);
char *_getline(void);
void rem_quotes(char *str);
void free_em(char **cmd, int count);

#endif