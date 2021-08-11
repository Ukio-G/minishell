/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:47:58 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 11:17:58 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# include "ft_vector/ft_vector.h"
# include "command.h"

# define NOT_SET (-1234567)

t_process_info	new_process_info(char *path, char **argv, char **envp);
pid_t			new_process(t_process_info info);
void			create_process_set(t_ft_vector create_process_set);
void			wait_all_processes(t_ft_vector process_info_set);
int				is_nonforkable(t_process_info info);

#endif
