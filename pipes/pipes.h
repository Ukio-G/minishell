#ifndef MINISHELL_PIPES_H
#define MINISHELL_PIPES_H

#include "../command.h"
#include "../ft_vector/ft_vector.h"

t_ft_vector		create_pipes_set(t_ft_vector commands);
void			bind_process_with_pipes(t_ft_vector processes, t_ft_vector pipes);
void close_all_pipes();

#endif //MINISHELL_PIPES_H
