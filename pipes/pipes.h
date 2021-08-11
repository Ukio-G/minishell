/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:47:25 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:22:40 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "command.h"
# include "ft_vector/ft_vector.h"

t_ft_vector	create_pipes_set(t_ft_vector commands);
void		bind_process_with_pipes(t_ft_vector processes, t_ft_vector pipes);
void		close_all_pipes(void);

#endif
