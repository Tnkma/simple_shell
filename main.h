#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#define WRITE_END 1
#define READ_END 0



#define PROMPT "$ "

/**
 * struct CmdArgs - struture forthe command
 * @args: the arugments
 * @count: count of the program
 */
typedef struct
{
	char **args; 
	int count;
} CmdArgs;

#include "shell.h"

#define print(c) (write(STDERR_FILENO, c, _strlen(c)))




#include "utils/utils.h"
#include "parsers/parser.h"
#include "cmd/cmd.h"
#include "executor/executor.h"
#include "tests/tests.h"

#endif
