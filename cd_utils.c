/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:30:53 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/08 12:30:53 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"



int	process_path(char **argv, char **current_path)
{
	char *temp;
	int len;
	char *home = find_env_by_key("HOME");// надо проверить, нашлась ли такая переменная окружения
	if((ft_strncmp("~", argv[1], ft_strlen(argv[1])) == 0) || (ft_strncmp("~/", argv[1], ft_strlen(argv[1])) == 0))
	{
		*current_path = home;
		return (0);
	}
	if (argv[1][0] == '~' && argv[1][1] == '/') //надо делать подстановку домашнего каталога вместо ~
	{
		if(argv[1][ft_strlen(argv[1]) - 1] == '/')
			argv[1][ft_strlen(argv[1]) - 1] = '\0';
		len = (int)ft_strlen(home) + (int)ft_strlen(argv[1]);
		temp = malloc(len);
		ft_memcpy(temp, home, ft_strlen(home));
		ft_memcpy(temp + ft_strlen(home), argv[1] + 1, ft_strlen(argv[1] + 1));
		temp[len] = '\0';
		*current_path = temp;
		return(0);
	}
	free(home);
	if (argv[1][0] == '-' && ft_strlen(argv[1]) == 1)
	{
		char *oldpwd = find_env_by_key("OLDPWD");
		if(oldpwd == 0)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set", 1);
			free(oldpwd);
			return (-1);
		}
		*current_path = oldpwd;
		return(0);
	}
	*current_path = ft_strdup(argv[1]);
	return(0);
}

