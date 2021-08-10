/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:40:31 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/08 17:16:46 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"

void	unset(char **argv)
{
	char	*value;
	int		i;

	i = 1;
	while (argv && argv[i])
	{
		value = find_env_by_key(argv[i]);
		if (value)
		{
			remove_env(argv[i]);
			free(value);
		}
		if (!is_valid_identifier(argv[i]))
			print_error_msg("unset", argv[i], "not a valid identifier");
		i++;
	}
}
