/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 03:25:36 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 10:53:53 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <redirection/redirection.h>
#include "preprocessor.h"
#include "libft.h"
#include "errors_printer/error_printer.h"
#include "shell_status/shell_status.h"

/*
 * Return pointer to first character after redirect and spaces.
 * Obtains pointer to first redirect character.
 * Example:
 * >> asdfg
 * |  |
 * |  rarg_start(redrection_position)
 * |
 * redrection_position
 */
char	*rarg_start(char *redirection_position)
{
	char	*start;

	start = redirection_position;
	start += (*start == start[1]);
	start++;
	start += (*start == '\02');
	if (*redirection_position == '>')
	{
		if (*start == '<')
			start = 0;
	}
	else if (*redirection_position == '<')
	{
		if (*start == '>')
			start = 0;
	}
	start += (*start == ' ');
	return (start);
}

/*
 * Return pointer to last character redirect's argument
 * Obtains pointer to first redirect character.
 * Example:
 * cat <file.a <file.b >file.c >>file.d >"file<>.e"qwert
 * |                                    |              |
 * source                      redirection_position    |
 *                                                     |
 *                              rarg_end(redirection_position, source)
 */
char	*rarg_end(char *redirection_position, char *source)
{
	char	*start;
	char	*end;

	start = rarg_start(redirection_position);
	if (!start)
		return (0);
	end = ft_strpbrk2(start, "\02><");
	while (*end && is_escaped(end, source, "\'\""))
	{
		end = ft_strpbrk2(start, "\02><");
	}
	end -= ft_isinset(*end, "\02><");
	while (*end == '\0')
		end--;
	return (end);
}

/*
 * Set substring - pair pointer to start and end of redirection's argument
 * Obtains array of 2 char*, where will written result, and redirection position
 */
void	rarg_substring(char *substring[2], char *start)
{
	substring[0] = rarg_start(start);
	substring[1] = rarg_end(start, start);
}

/*
 * Find last input and output redirections
 * redirections[LAST_OUT] - contains last out redirection (>> or >)
 * redirections[LAST_IN] - contains las input redirection (<< or <)
 * Will keep a pointer to the first character of redirection ( especially
 * relevant for cases >> <<)
 * Example:
 * cat <file.a <file.b >file.c >>file.d >file.e
 *             |                        |
 *       redirections[LAST_IN] |
 *                                      |
 *                      redirections[LAST_OUT]
 */
void	find_last_redirection(char *redirections[3], char *source)
{
	char	*redirection;

	redirection = ft_strpbrk2(source, "><");
	while (redirection && *redirection)
	{
		if (!is_escaped(redirection, source, "\'\""))
		{
			if (*redirection == '>')
				redirections[LAST_OUT] = redirection;
			else if (*redirection == '<')
				redirections[LAST_IN] = redirection;
			redirection += (redirection[1] == '>')
				+ (redirection[1] == '<') + 1;
			redirection = ft_strpbrk2(redirection, "><");
		}
		else
		{
			redirection++;
		}
	}
}

/*
 * Find last redirection's argument character
 * Obtaining:
 * redirections - last input and output redirections
 * source - start of string
 * Save result to redirections[END_REDIRECTIONS_STRING]
 * redirections
 * Example:
 * cat <file.a <file.b >file.c >>file.d >file.e
 * |           |                        |     |
 * source      |                        |     |
 *             |                        |     |
 *       redirections[LAST_IN] |     |
 *                                      |     |
 *                      redirections[LAST_OUT]
 *                                            |
 *                    redirections[END_REDIRECTIONS_STRING]
 */
void	find_end_redirection_string(char *redirections[3], char *source)
{
	char	*end;

	if (redirections[LAST_IN] > redirections[LAST_OUT])
		end = redirections[LAST_IN];
	else
		end = redirections[LAST_OUT];
	redirections[END_REDIRECTIONS_STRING] = rarg_end(end, source);
}
