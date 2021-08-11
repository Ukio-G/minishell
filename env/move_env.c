/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:10:42 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/11 13:23:16 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "env_utils.h"

void	remove_env(char *key)
{
	int		num;
	char	*key_value_str;
	char	*new_key_value_str;

	num = find_number_of_key(key);
	key_value_str = get_status()->envp[num];
	new_key_value_str = ft_calloc(1, (ft_strlen(key_value_str) + 2));
	printf("LEAK %s:%i %p\n", __FILE__, __LINE__,  new_key_value_str);
	new_key_value_str[0] = INVISIBLE_PREFIX;
	ft_memcpy(new_key_value_str + 1, key_value_str, ft_strlen(key_value_str));
	free(key_value_str);
	get_status()->envp[num] = new_key_value_str;
	return ;
}

char	**copy_env(char **orig_env)
{
	char	**res;
	int		size;
	int		i;

	i = 0;
	size = get_2d_array_size(orig_env);
	res = malloc((size + 1) * sizeof(char *));
	printf("LEAK %s:%i %p\n", __FILE__, __LINE__,  res);
	if (res)
	{
		while (i < size)
		{
			res[i] = ft_strdup(orig_env[i]);
			printf("LEAK %s:%i %p\n", __FILE__, __LINE__,  res[i]);
			i++;
		}
		res[i] = 0;
	}
	return (res);
}
