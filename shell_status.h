#ifndef MINISHELL_SHELL_STATUS_H
#define MINISHELL_SHELL_STATUS_H

#include <stdlib.h>

typedef struct s_shell_status
{
	char **envp;
	char **argv;
	char *home;
	int uid;
	int gid;
} t_shell_status;


t_shell_status *init_status(char **argv, char **envp);
t_shell_status *get_status();
char * find_env_by_key(char * str);

#endif //MINISHELL_SHELL_STATUS_H
