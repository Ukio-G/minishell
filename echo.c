/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 15:29:29 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/07 17:38:08 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"

static int	is_arg_exist(char **argv, int *n_flag)
{
	if (argv[1] == 0)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (1);
}

static void	process_arg(char **argv, int n_flag)
{
	int	argv_len;
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	argv_len = get_2d_array_size(argv);
	while (i < argv_len)
	{
		if (n_flag)
		{
			while ((ft_strncmp(argv[i], "-n", ft_strlen(argv[i]))) == 0
				&& flag == 0)
				i++;
		}
		ft_putstr_fd(argv[i], 1);
		flag = 1;
		if (i != argv_len - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

void	echo(char **argv)
{
	int	n_flag;

	n_flag = 0;
	if (!is_arg_exist(argv, &n_flag))
		return ;
	if ((ft_strncmp(argv[1], "-n", ft_strlen(argv[1]))) == 0)
	{
		n_flag = 1;
		argv = argv + 1;
	}
	process_arg(argv, n_flag);
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return ;
}
