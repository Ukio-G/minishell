/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:47:33 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 13:17:58 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <redirection/redirection.h>
#include "preprocessor.h"
#include "libft.h"
#include "errors_printer/error_printer.h"
#include "shell_status/shell_status.h"

int	expanded_variables_length(char *start_position)
{
	char	*dollar_position;
	int		result;
	int		variable_len;
	char	*v[2];

	dollar_position = ft_strchr(start_position, '$');
	result = 0;
	while (dollar_position)
	{
		variable_len = expanded_variables_length_loop(dollar_position,
				start_position, v, &result);
		dollar_position += (variable_len == 0);
		dollar_position = ft_strchr(dollar_position + variable_len, '$');
	}
	return (result);
}

/*
 * Return size of new string, after expanding all variables, without
 * null-terminated character
 * example:
 * $USER is "atawana"
 * source = "ls -lah $USER"
 * result: 15
 */
int	expanded_string_length(char *source)
{
	int	input_length;
	int	vars_length;
	int	expanded_vars_length;
	int	no_vars_length;

	input_length = (int) ft_strlen(source);
	vars_length = variables_length(source);
	expanded_vars_length = expanded_variables_length(source);
	no_vars_length = input_length - vars_length;
	return (no_vars_length + expanded_vars_length);
}

void	expand_variable(char **source, char *pos[3], char *v[2])
{
	ft_memcpy(pos[W_POS], pos[R_POS], pos[D_POS] - pos[R_POS]);
	pos[W_POS] += (pos[D_POS] - pos[R_POS]);
	v[V_NAME] = variable_name(*source, pos[D_POS]);
	v[V_VAL] = find_env_by_key(v[V_NAME]);
	ft_memcpy(pos[W_POS], v[V_VAL], ft_strlen(v[V_VAL]));
	pos[W_POS] += ft_strlen(v[V_VAL]);
	pos[R_POS] += ft_strlen(v[V_NAME]) + (pos[D_POS] - pos[R_POS]) + 1;
	free(v[V_NAME]);
	free(v[V_VAL]);
}

char	*preprocess_variables(char *source)
{
	char	*result;
	char	*pos[3];
	char	*v[2];

	result = ft_calloc(1, (size_t) expanded_string_length(source) + 2);
	pos[W_POS] = result;
	pos[R_POS] = source;
	pos[D_POS] = ft_strchr2(source, '$');
	if (*pos[D_POS] == 0)
		ft_memcpy(result, source, ft_strlen(source));
	else
		while (*pos[D_POS])
			preprocess_variables_loop(pos, v, source);
	return (result);
}
