/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:47:33 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:24:13 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <redirection/redirection.h>
#include "preprocessor.h"
#include "libft.h"
#include "errors_printer/error_printer.h"
#include "shell_status/shell_status.h"

int expanded_variables_length(char *start_position)
{
	char *dollar_position;
	int result;
	int variable_len;
	char *v[2];
	dollar_position = ft_strchr(start_position, '$');
	result = 0;
	while (dollar_position)
	{
		if (!is_escaped(dollar_position, start_position, "'"))
		{
			v[VARIABLE_NAME] = variable_name(start_position, dollar_position);
			v[VARIABLE_VALUE] = find_env_by_key(v[VARIABLE_NAME]);
			variable_len = (int) ft_strlen(v[VARIABLE_NAME]);
			result += (int) ft_strlen(v[VARIABLE_VALUE]);
			free(v[VARIABLE_NAME]);
			free(v[VARIABLE_VALUE]);
		}
		else
		{
		    v[VARIABLE_NAME] = variable_name(start_position, dollar_position);
		    variable_len = (int) ft_strlen(v[VARIABLE_NAME]);
		    free(v[VARIABLE_NAME]);
		}
		dollar_position += (variable_len == 0);
		dollar_position = ft_strchr(dollar_position + variable_len, '$');
	}
	return result;
}

/*
 * Return size of new string, after expanding all variables, without null-terminated character
 * example:
 * $USER is "atawana"
 * source = "ls -lah $USER"
 * result: 15
 */
int expanded_string_length(char *source)
{
	int input_length;
	int vars_length;
	int expanded_vars_length;
	int no_vars_length;
	input_length = (int) ft_strlen(source);
	vars_length = variables_length(source);
	expanded_vars_length = expanded_variables_length(source);
	no_vars_length = input_length - vars_length;
	return no_vars_length + expanded_vars_length;
}

void expand_variable(char **source, char *pos[3], char *v[2])
{
	// Copy before dollar
	ft_memcpy(pos[WRITE_POS], pos[READ_POS], pos[DOLLAR_POS] - pos[READ_POS]);

	// Move write position
	pos[WRITE_POS] += (pos[DOLLAR_POS] - pos[READ_POS]);

	// Determinate pair key => value
	v[VARIABLE_NAME] = variable_name(*source, pos[DOLLAR_POS]);
	v[VARIABLE_VALUE] = find_env_by_key(v[VARIABLE_NAME]);

	// Copy variable value
	ft_memcpy(pos[WRITE_POS], v[VARIABLE_VALUE], ft_strlen(v[VARIABLE_VALUE]));

	// Move read and write position
	pos[WRITE_POS] += ft_strlen(v[VARIABLE_VALUE]);
	pos[READ_POS] +=
			ft_strlen(v[VARIABLE_NAME]) + (pos[DOLLAR_POS] - pos[READ_POS]) + 1;

	// Free used resources
	free(v[VARIABLE_NAME]);
	free(v[VARIABLE_VALUE]);
}

char *preprocess_variables(char *source)
{
	char *result;
	char *pos[3];
	char *v[2];

	result = ft_calloc(1, (size_t) expanded_string_length(source) + 2);
	pos[WRITE_POS] = result;
	pos[READ_POS] = source;
	pos[DOLLAR_POS] = ft_strchr2(source, '$');
	if (*pos[DOLLAR_POS] == 0)
		ft_memcpy(result, source, ft_strlen(source));
	else
		while (*pos[DOLLAR_POS])
		{
			if (!is_escaped(pos[DOLLAR_POS], source, "\'"))
				expand_variable(&source, pos, v);
			else
			{
				pos[DOLLAR_POS] = ft_strchr2(pos[DOLLAR_POS] + 1, '$');
				if (*pos[DOLLAR_POS] == 0)
					ft_memcpy(pos[WRITE_POS], pos[READ_POS],pos[DOLLAR_POS] - pos[READ_POS]);
				continue;
			}
			pos[DOLLAR_POS] = ft_strchr2(pos[READ_POS], '$');
			if (*pos[DOLLAR_POS] == 0)
				ft_memcpy(pos[WRITE_POS], pos[READ_POS],pos[DOLLAR_POS] - pos[READ_POS]);
		}
	return result;
}