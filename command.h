#ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H

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
} t_process_info;


# endif
