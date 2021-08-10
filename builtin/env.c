/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:37:54 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/10 21:41:59 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"

void	env(void)
{
	char	**temp;
	int		i;

	i = 0;
	temp = get_status()->envp;
	while (temp[i])
	{
		if(temp[i][0] == INVISIBLE_PREFIX)
		{
			i++;
			continue;
		}
		ft_putstr_fd(temp[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
