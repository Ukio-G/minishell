//
// Created by Leesa Weeper on 8/7/21.
//

#ifndef MINISHELL_BASIC_SHELL_H
#define MINISHELL_BASIC_SHELL_H

#include "libft.h"
#include "env_utils.h"
#include <sys/stat.h>
#include "shell_status.h"

size_t get_2d_array_size(char **array);
int find_number_of_key(char *key);
void echo (t_process_info *info);
void cd(t_process_info *info);
int	process_path(char **argv, char **current_path);
void pwd(void);
void export (t_process_info *info);
void unset(t_process_info *info);
void env(void);
void ft_exit(void);



#endif //MINISHELL_BASIC_SHELL_H
