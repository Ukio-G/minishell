/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:51:04 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/08 18:30:17 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"

static void	swap_string_in_array(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

static char	**sort_env(void)
{
	char	**temp;
	int		i;
	int		j;
	int		size;
	int		len;

	temp = get_status()->envp;
	size = get_2d_array_size(temp);
	i = 0;
	while (i < size - 1)
	{
		j = size - 1;
		while (j > i)
		{
			len = ft_strlen(temp[j]);
			if (len < ft_strlen(temp[j - 1]))
				len = ft_strlen(temp[j - 1]);
			if (ft_strncmp(temp[j - 1], temp[j], len) > 0)
				swap_string_in_array(&temp[j - 1], &temp[j]);
			j--;
		}
		i++;
	}
	return (temp);
}

static void	print_exp_env(char **env)
{
	int		i;
	char	**pair;

	i = 0;
	while (env[i])
	{
		if (env[i][0] != INVISIBLE_PREFIX)
		{
			ft_putstr_fd("declare -x ", 1);
			pair = ft_split(env[i], '=');
			ft_putstr_fd(pair[0], 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(pair[1], 1);
			ft_putstr_fd("\"\n", 1);
			ft_split_free(pair);
		}
		i++;
	}
	return ;
}

void	process_var(char *var)
{
	char	**key_value;
	char	*key;

	key_value = ft_split(var, '=');
	key = key_value[0];
	if (!is_valid_identifier(key))
	{
		print_error_msg("export", var, "not a valid identifier");
		return ;
	}
	if (ft_split_count(key_value) > 1)
		update_env(key, var + ft_strlen(key) + 1);
	ft_split_free(key_value);
	return ;
}

void	export(char **argv)
{
	int	i;
	int	argv_size;

	argv_size = get_2d_array_size(argv);
	if (argv_size == 1)
	{
		print_exp_env(sort_env());
		return ;
	}
	i = 1;
	while (i < argv_size)
	{
		process_var(argv[i]);
		i++;
	}
	return ;
}
