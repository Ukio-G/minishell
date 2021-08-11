/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 03:25:19 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 10:45:37 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <redirection/redirection.h>
#include "preprocessor.h"
#include "libft.h"
#include "errors_printer/error_printer.h"
#include "shell_status/shell_status.h"

void	find_substr(char *substr[2], char *start_str, char *escape_chars)
{
	(substr)[0] = ft_strpbrk(start_str, escape_chars);
	if ((substr)[0])
	{
		(substr)[1] = ft_strchr((substr)[0] + 1, *(substr)[0]);
	}
}

void	remove_substring(char *str, char *substr[2])
{
	char	*end;
	int		char_removed;
	int		shift_count;

	if (!substr[0] || !substr[1] || !str)
		return ;
	char_removed = (int)(substr[1] - substr[0] + 1);
	end = ft_strlen(str) + str;
	shift_count = (int)(end - substr[1]) - 1;
	ft_memmove(substr[0], substr[1] + 1, shift_count);
	ft_memset(end - (int)char_removed, 0, char_removed);
}

int	is_escaped(char *char_ptr, char *start_str, char *escape_chars)
{
	char	*substr[2];

	find_substr(substr, start_str, escape_chars);
	if (substr[0] && substr[1])
	{
		if (char_ptr < substr[0])
		{
			return (0);
		}
		else if (char_ptr > substr[1])
		{
			return (is_escaped(char_ptr, substr[1] + 1, escape_chars));
		}
		else if (char_ptr == substr[0] || char_ptr == substr[1])
		{
			return (0);
		}
		else if (substr[0] < char_ptr && char_ptr < substr[1])
		{
			return (1);
		}
	}
	return (0);
}

char	*preprocess_pipes(char *source)
{
	char	*pipe_position;
	char	*result;

	result = ft_strdup(source);
	if (!result)
	{
		exit(MINISHELL_MEMORY_ERROR);
	}
	pipe_position = ft_strchr(result, '|');
	while (pipe_position)
	{
		if (!is_escaped(pipe_position, result, "\"\'"))
		{
			*pipe_position = SPECIAL_PIPE;
		}
		pipe_position = ft_strchr(pipe_position + 1, '|');
	}
	return (result);
}

char	*preprocess_spaces(char *source)
{
	char	*space_position;
	char	*result;

	result = ft_strdup(source);
	if (!result)
	{
		exit(MINISHELL_MEMORY_ERROR);
	}
	space_position = ft_strchr(result, ' ');
	while (space_position)
	{
		if (!is_escaped(space_position, result, "\"'"))
		{
			*space_position = SPECIAL_ARGS_DELIMITER;
		}
		space_position = ft_strchr(space_position + 1, ' ');
	}
	return (result);
}
