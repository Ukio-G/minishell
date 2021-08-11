/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:48:40 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 02:54:23 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <libft.h>
#include "signal.h"
#include <stdio.h>
#include "rl/readline.h"

void	s_ctrl_slash(void)
{
	waitpid(-1, NULL, WNOHANG);
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	s_ctrl_c(void)
{
	int pid;
	pid = waitpid(-1, NULL, WNOHANG);
	if (pid)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		write(1, "\n", 1);
		rl_replace_line("\0", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_d_handler(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void s_init()
{
	signal(SIGQUIT, (void *)s_ctrl_slash);
	signal(SIGINT, (void *)s_ctrl_c);
}
