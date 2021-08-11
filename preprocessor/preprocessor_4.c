/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 03:25:42 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 10:58:03 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <redirection/redirection.h>
#include "preprocessor.h"
#include "libft.h"
#include "errors_printer/error_printer.h"
#include "shell_status/shell_status.h"

char	*redirection_argument_new(char *redirection)
{
	char	*substring[2];
	char	*result;

	rarg_substring(substring, redirection);
	if (!substring[0] || !substring[1])
		return (0);
	result = ft_calloc((substring[1] - substring[0]) + 2, 1);
	if (result)
		ft_slice_cpy(result, substring[0], substring[1]);
	return (result);
}

void	remove_redirections(char *redirections[3], char *source)
{
	char	*substring[2];
	char	*first;
	char	*second;

	if (redirections[LAST_OUT] > redirections[LAST_IN])
		first = redirections[LAST_OUT];
	else
		first = redirections[LAST_IN];
	if (redirections[LAST_OUT] > redirections[LAST_IN])
		second = redirections[LAST_IN];
	else
		second = redirections[LAST_OUT];
	if (first)
	{
		substring[0] = first;
		substring[1] = rarg_end(first, source);
		remove_substring(source, substring);
	}
	if (second)
	{
		substring[0] = second;
		substring[1] = rarg_end(second, source);
		remove_substring(source, substring);
	}
}

char	*preprocess_redirection(char *source)
{
	char	*result;
	char	*trimmed;
	char	*redirection[3];

	result = ft_strdup(source);
	ft_memset(redirection, 0, sizeof(void *) * 3);
	find_last_redirection(redirection, result);
	set_status_redirection(redirection);
	while (redirection[LAST_IN] || redirection[LAST_OUT])
	{
		if (redirection[LAST_OUT])
			create_redirection_file(redirection[LAST_OUT]);
		remove_redirections(redirection, result);
		ft_memset(redirection, 0, sizeof(void *) * 3);
		find_last_redirection(redirection, result);
	}
	trimmed = ft_strtrim(result, "\02");
	free(result);
	return (trimmed);
}

char	*preprocess(char *raw_input)
{
	char	*pipes;
	char	*spaces;
	char	*variables;
	char	*redirection;

	init_redirection(&get_status()->redirect);
	pipes = preprocess_pipes(raw_input);
	spaces = preprocess_spaces(pipes);
	variables = preprocess_variables(spaces);
	redirection = preprocess_redirection(variables);
	if (*redirection == SPECIAL_PIPE)
		print_pipe_error();
	if (ft_strncmp(redirection, ".", 2) == 0)
		print_dot_error();
	free(pipes);
	free(spaces);
	free(variables);
	return (redirection);
}
