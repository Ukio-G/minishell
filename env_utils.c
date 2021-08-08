/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 18:38:20 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/08 20:26:35 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"

size_t	get_2d_array_size(char **array)
{
	size_t	size;

	size = 0;
	while (*array != 0)
	{
		array++;
		size++;
	}
	return (size);
}

int	is_valid_identifier(char *id)
{
	int	i;

	i = 1;
	if (id)
	{
		if (!ft_isalpha(id[0]) && id[0] != '_')
			return (0);
		while (id[i])
		{
			if (!ft_isalpha(id[i]) && !ft_isdigit(id[i]) && id[0] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

void	print_error_msg(char *op, char *bad_id, char *msg)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(op, 1);
	ft_putstr_fd(": `", 1);
	ft_putstr_fd(bad_id, 1);
	ft_putstr_fd("\': ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}
