/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 19:53:49 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/11 13:23:16 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "env_utils.h"

void	add_if_is(char *key, char *value, int key_num, int update_len)
{
	char	*upd_str;

	upd_str = (char *)malloc(update_len);
	ft_memcpy(upd_str, key, ft_strlen(key));
	upd_str[ft_strlen(key)] = '=';
	ft_memcpy(upd_str + ft_strlen(key) + 1, value, ft_strlen(value));
	upd_str[update_len - 1] = '\0';
	free(get_status()->envp[key_num]);
	get_status()->envp[key_num] = upd_str;
}

void	add_if_not(char *key, char *value, int update_len, int size)
{
	char	**upd_env;
	int		i;
	char	*upd_str;

	i = 0;
	upd_env = malloc((size + 2) * sizeof(char *));
	if (upd_env)
	{
		while (i < size)
		{
			upd_env[i] = ft_strdup(get_status()->envp[i]);
			free(get_status()->envp[i]);
			i++;
		}
		upd_str = (char *) malloc(update_len);
		ft_memcpy(upd_str, key, ft_strlen(key));
		upd_str[ft_strlen(key)] = '=';
		ft_memcpy(upd_str + ft_strlen(key) + 1, value, ft_strlen(value));
		upd_str[update_len - 1] = '\0';
		upd_env[i] = upd_str;
		upd_env[i + 1] = 0;
		free(get_status()->envp);
		get_status()->envp = upd_env;
	}
}

void	update_env(char *key, char *value)
{
	int		key_num;
	int		update_len;
	int		size;

	size = get_2d_array_size(get_status()->envp);
	key_num = find_number_of_key(key);
	update_len = ft_strlen(key) + ft_strlen(value) + 2;
	if (key_num >= 0)
		add_if_is(key, value, key_num, update_len);
	else
		add_if_not(key, value, update_len, size);
	return ;
}
