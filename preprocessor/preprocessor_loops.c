/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor_loops.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 10:36:29 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 13:48:24 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env_utils.h>
#include <printf.h>
#include "preprocessor.h"
#include "libft.h"

void	preprocess_argument_loop(char *pos[2], char *substr[2])
{
	if (pos[R_POS] < substr[0])
	{
		ft_slice_cpy(pos[W_POS], pos[R_POS], substr[0] - 1);
		pos[W_POS] += (substr[0] - pos[R_POS]);
	}
	substr[1] = ft_strchr(substr[0] + 1, *substr[0]);
	if ((substr[1] - substr[0]) > 1)
	{
		ft_slice_cpy(pos[W_POS], substr[0] + 1, substr[1] - 1);
		pos[W_POS] += (substr[1] - substr[0]) - 1;
	}
	substr[0] = ft_strpbrk2(substr[1] + 1, "\"\'");
	pos[R_POS] = substr[1] + 1;
	if (!*substr[0])
		ft_slice_cpy(pos[W_POS], pos[R_POS], substr[0] - 1);
}

void	preprocess_variables_loop(char *pos[3], char *v[2], char *source)
{
	if (!is_escaped(pos[D_POS], source, "\'"))
		expand_variable(&source, pos, v);
	else
	{
		pos[D_POS] = ft_strchr2(pos[D_POS] + 1, '$');
		if (*pos[D_POS] == 0)
			ft_memcpy(pos[W_POS], pos[R_POS], pos[D_POS] - pos[R_POS]);
		return ;
	}
	pos[D_POS] = ft_strchr2(pos[R_POS], '$');
	if (*pos[D_POS] == 0)
		ft_memcpy(pos[W_POS], pos[R_POS], pos[D_POS] - pos[R_POS]);
}

int	expanded_variables_length_loop(char *dollar_position,
	char *start_position, char *v[2], int *result)
{
	int	variable_len;

	variable_len = 0;
	if (!is_escaped(dollar_position, start_position, "'"))
	{
		v[V_NAME] = variable_name(start_position, dollar_position);
		v[V_VAL] = find_env_by_key(v[V_NAME]);
		variable_len = (int) ft_strlen(v[V_NAME]);
		*result += (int) ft_strlen(v[V_VAL]);
		free(v[V_NAME]);
		free(v[V_VAL]);
	}
	else
	{
		v[V_NAME] = variable_name(start_position, dollar_position);
		variable_len = (int) ft_strlen(v[V_NAME]);
		free(v[V_NAME]);
	}
	return (variable_len);
}
