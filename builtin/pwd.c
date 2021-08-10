/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:45:35 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/08 12:49:24 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"

void	pwd(void)
{
	char	*buffer_pwd;

	buffer_pwd = getcwd(NULL, 0);
	ft_putstr_fd(buffer_pwd, 1);
	ft_putstr_fd("\n", 1);
	if (buffer_pwd)
		free(buffer_pwd);
	return ;
}
