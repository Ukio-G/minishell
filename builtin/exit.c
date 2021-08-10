/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:21:09 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/08 17:21:25 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"

void	ft_exit(void)
{
	int	exit_status;

	exit_status = ft_atoi(find_env_by_key("?"));
	ft_putstr_fd("exit\n", 1);
	exit(exit_status);
}
