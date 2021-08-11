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

#include <printf.h>
#include "basic_shell.h"

void	ft_exit(void)
{
	int	exit_status;
	char *tmp_leak;

	tmp_leak = find_env_by_key("?");
	printf("LEAK %s:%i %p\n", __FILE__, __LINE__,  tmp_leak);
	exit_status = ft_atoi(tmp_leak);
	ft_putstr_fd("exit\n", 1);
	exit(exit_status);
}
