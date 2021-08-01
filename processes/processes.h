#ifndef MINISHELL_PROCESSES_H
#define MINISHELL_PROCESSES_H

#include "../ft_vector/ft_vector.h"

#define NOT_SET -1234567

t_process_info new_process_info(char *path, char **argv, char **envp);
pid_t new_process(t_process_info info);
void create_process_set(t_ft_vector create_process_set);
void wait_all_processes(t_ft_vector process_info_set);
void stop_all_processes(t_ft_vector process_info_set);

#endif
