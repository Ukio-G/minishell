/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:47:19 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:21:57 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <processes/processes.h>
#include "libft.h"
#include "pipes.h"
#include "ft_vector/ft_vector.h"
#include "shell_status/shell_status.h"

t_ft_vector	create_pipes_set(t_ft_vector commands)
{
	t_ft_vector	result;
	int			tmp[2];
	int			i;

	i = 0;
	ft_vector_init(&result, sizeof(int));
	while (i < (int)commands.size - 1)
	{
		pipe(tmp);
		ft_vector_add(&result, tmp + 1);
		ft_vector_add(&result, tmp);
		i++;
	}
	return (result);
}

void	close_all_pipes(void)
{
	t_ft_vector	pset;
	int			*fd;

	pset = get_status()->pipes_set;
	while (ft_vector_iter(&pset))
	{
		fd = ft_vector_iter_value(&pset);
		close(*fd);
	}
}

void	bind_process_with_pipes(t_ft_vector processes, t_ft_vector pipes)
{
	t_process_info	*info[2];
	int				i;
	int				j;

	i = 0;
	j = 0;
	while ((int)processes.size - 1 > i)
	{
		info[0] = at(&processes, i);
		info[1] = at(&processes, i + 1);
		info[0]->out_d = *(int *)at(&pipes, j);
		info[1]->in_d = *(int *)at(&pipes, j + 1);
		j += 2;
		i++;
	}
}

void	pipes_replace(t_process_info info)
{
	if (info.in_d != NOT_SET)
		dup2(info.in_d, STDIN_FILENO);
	if (info.out_d != NOT_SET)
		dup2(info.out_d, STDOUT_FILENO);
	close_all_pipes();
}
