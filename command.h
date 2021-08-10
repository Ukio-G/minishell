#ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H
# include "stdlib.h"
# include <unistd.h>
#include "executable_file_error.h"

typedef struct s_process_info
{
	char *bin_path;
	char **argv;
	char **envp;
	int in_d;
	int out_d;
	pid_t pid;
	int exit_code;
	int is_builtin;
	t_executable_file_error error;
} t_process_info;


# endif
