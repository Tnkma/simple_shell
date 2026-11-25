#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define WRITE_END 1
#define READ_END 0

#include "../parsers/parser.h"
#include "../executor/executor.h"
#include "../cmd/cmd.h"


void _print(const char *str);
void print_int(int num);
void print_exit_error(char *input, shellInfo *shell);
int print_echo(char **cmd);


int _putchar(char c);
void print_int(int num);


void print_numbers(int n);
void _print_error(char *input, shellInfo *shell);


/* String functions */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(const char *s);
int _atoi(char *s);
char *_strchr(char *s, char c);
int _strcmp(char *s1, char *s2);

#endif