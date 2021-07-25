#ifndef MINISHELL_COMMAND_H
# define MINISHELL_COMMAND_H

typedef struct s_process_info
{
	char *bin_path;
	char **argv;
	char **envp;
} t_process_info;

t_process_info new_process_info(char *path, char **argv, char **envp);
int new_process(t_process_info info);

# endif
