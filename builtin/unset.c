/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:40:31 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/11 00:20:30 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "basic_shell.h"

int	unset(t_process_info *info)
{
	char	*value;
	int		i;
	char	**argv;
	int		exit_status;

	exit_status = 0;
	argv = info->argv;
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
		{
			print_error_msg("unset", argv[i], "not a valid identifier");
			exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}
