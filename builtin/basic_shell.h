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
void echo (char **argv);
void cd(char **argv);
int	process_path(char **argv, char **current_path);
void pwd();
void export (char **argv);
void unset(char **argv);
void env(void);
void ft_exit();



#endif //MINISHELL_BASIC_SHELL_H
