/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:30:53 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/11 15:44:43 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "basic_shell.h"

int	process_tilda(char **argv, char **current_path)
{
	char	*temp;
	char	*home;

	home = find_env_by_key("HOME");
	if (!home)
		home = find_env_by_invisible_key("HOME");
	if ((ft_strncmp("~", argv[1], ft_strlen(argv[1])) == 0)
		|| (ft_strncmp("~/", argv[1], ft_strlen(argv[1])) == 0))
	{
		*current_path = home;
		return (0);
	}
	if (argv[1][0] == '~' && argv[1][1] == '/')
	{
		if (argv[1][ft_strlen(argv[1]) - 1] == '/')
			argv[1][ft_strlen(argv[1]) - 1] = '\0';
		temp = malloc((int)ft_strlen(home) + (int)ft_strlen(argv[1]));
		ft_memcpy(temp, home, ft_strlen(home));
		ft_memcpy(temp + ft_strlen(home), argv[1] + 1, ft_strlen(argv[1] + 1));
		temp[(int)ft_strlen(home) + (int)ft_strlen(argv[1])] = '\0';
		*current_path = temp;
		return (0);
	}
	free(home);
	return (1);
}

int	process_path(char **argv, char **current_path)
{
	char	*oldpwd;

	if (!process_tilda(argv, current_path))
		return (0);
	if (argv[1][0] == '-' && ft_strlen(argv[1]) == 1)
	{
		oldpwd = find_env_by_key("OLDPWD");
		if (oldpwd == 0)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 1);
			free(oldpwd);
			return (-1);
		}
		*current_path = oldpwd;
		return (0);
	}
	*current_path = ft_strdup(argv[1]);
	return (0);
}
