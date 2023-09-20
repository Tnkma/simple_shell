#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define WRITE_END 1
#define READ_END 0

/**
 * struct CmdArgs - struture forthe command
 * @args: the arugments
 * @count: count of the program
 */
typedef struct CmdArgs
{
	char **args;
	int count;
} CmdArgs;

#define print(c) (write(STDERR_FILENO, c, _strlen(c)))
char *_getline(void);
void read_input(char **argv, char **envp);
int handle_cmd(char *lineptr, int c, char **argv, char **envp);
void _print_error(char *input, int count, char *p_name);
void fix_print(int num);
void print_numbers(int n);
int _getppid(char **args, int *status_for_exit);
int logical_op(char *lineptr, char **env);
int execute_log_command(char *command, char **env);
int logical_or(char *lineptr, char **env);
int logical_co(char *lineptr, char **env);
void print_exit_error(char *p_name, int count, int num);
char *e_space(char *str);
int print_echo(char **cmd);
char *fix_newline(char *str);
void free_em(char **cmd, int count);
int wait_status(int status);



#include <sys/wait.h>
void _print(const char *str);
int get_loc(char *arg, char **args, char **env);
char *loc(char *path, char *arg, char **args, char **env);
char *_strdup(const char *s);
int built_cmd(char **arg, char **envp, int *status_for_exit, int count);
void change_directory(char **args);
void set_env_var(char **args);
void unset_env_var(char **args);
void d_exit(char **args, int *status_for_exit, char *p_name, int count);
void _env(char **envp);
int fork_cmd(char **args, char **env, char *p_name, int cmd_count);
int handle_cmd_sep(char *lineptr, char **envp, char *p_name, int c, int *exit);

char *_strtok(char *str, const char *delim);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);
char *_strchr(char *s, char c);



void handle_cmd_b4pipe(int write_fd, char *cmd, char **envp);
void exec_cmd4_pipe(int inputed_fd, char *cmd, char **envp);
void exec_pipe_cmd(char *cmd, char **envp);
void rem_quotes(char *str);
int pipes_(char *a[], char *b[], char **env);
int redirection_(char *a[], char type_red[], char *b[], char **env);
int pipes_redirection(char *argv[], int argc, char **env);
CmdArgs split_line(char *line);
void handle_pipe_commands(char *lineptr, char **envp);
size_t command_exists(char *command);

#endif
