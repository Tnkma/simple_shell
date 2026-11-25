#ifndef SHELL_H
#define SHELL_H

/**
 * shellInfo Structure to hold shell information
 * @envp: The environment variables
 * @program_name: Name of the shell program
 * @cmd_count: Count of commands executed
 * @exit_status: Exit status of the last executed command
 */

typedef struct
{
	char **envp;
	char *program_name;
	int cmd_count;
	int exit_status;  
} shellInfo;

#endif

/*ping -c 1 google.com > /dev/null && echo "Online" || echo "Offline"*/
