/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:01:57 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/11 15:44:43 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <main_functions/main_functions.h>
#include "env_utils.h"

char	*find_env_by_key(char *str)
{
	char	**envp;
	char	*result;
	char	**pair;

	envp = get_status()->envp;
	result = 0;
	while (envp && !result && *envp)
	{
		pair = ft_split(*envp, '=');
		if (ft_strncmp(pair[0], str, ft_strlen(str) + 1) == 0)
		{
			result = ft_strdup(pair[1]);
		}
		ft_split_free(pair);
		envp++;
	}
	return (result);
}

char	*find_env_by_invisible_key(char *str)
{
	char	**envp;
	char	*result;
	char	**pair;

	envp = get_status()->envp;
	result = 0;
	while (envp && !result && *envp)
	{
		pair = ft_split(*envp, '=');
		if ((ft_strncmp(pair[0] + 1, str, ft_strlen(str) + 1) == 0)
			&& (*pair[0] == INVISIBLE_PREFIX))
		{
			result = ft_strdup(pair[1]);
			ft_split_free(pair);
		}
		envp++;
	}
	return (result);
}

int	get_int_from_env(char *key)
{
	char	*tmp;
	int		result;

	result = INT_MIN_MINISHELL;
	tmp = find_env_by_key(key);
	if (tmp)
	{
		result = ft_atoi(tmp);
		free(tmp);
	}
	return (result);
}

int	find_number_of_key(char *key)
{
	char	**env;
	int		i;
	char	**pair;

	i = 0;
	env = get_status()->envp;
	while (env[i])
	{
		pair = ft_split(env[i], '=');
		if ((ft_strncmp(pair[0], key, ft_strlen(key) + 1) == 0)
			|| ((ft_strncmp(pair[0] + 1, key, ft_strlen(key) + 1) == 0)
				&& (pair[0][0] == INVISIBLE_PREFIX)))
		{
			ft_split_free(pair);
			return (i);
		}
		ft_split_free(pair);
		i++;
	}
	return (-1);
}
