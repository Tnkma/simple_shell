/**
 * @file builtin.h
 * @brief Header file for built-in command functions.
 * 
 */

 #ifndef CMD_H
 #define CMD_H

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
#include "../executor/executor.h"



int built_cmd(char **args, char **envp, int *status_for_exit);
int change_directory(char **args);
int command_exists(char *command);


 #endif