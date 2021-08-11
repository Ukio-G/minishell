/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:25:28 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 11:28:37 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <file_utils.h>
#include <errors_printer/error_printer.h>
#include "redirection.h"
#include "shell_status/shell_status.h"
#include "preprocessor/preprocessor.h"

t_redirect_type	redirect_type(char *start_position)
{
	if (*start_position == '>')
	{
		if (start_position[1] == '>')
			return (R_DOUBLE_OUT);
		else
			return (R_SINGLE_OUT);
	}
	else if (*start_position == '<')
	{
		if (start_position[1] == '<')
			return (R_DOUBLE_INPUT);
		else
			return (R_SINGLE_INPUT);
	}
	return (0);
}

void	init_redirection(t_redirect *redirect)
{
	ft_memset(redirect, 0, sizeof(t_redirect));
	redirect->out_fd = -1;
	redirect->in_fd = -1;
	redirect->input_type = R_NO_TYPE;
	redirect->output_type = R_NO_TYPE;
}

void	create_or_clean(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (!fd)
	{
		ft_putstr_fd("Ambiguous redirect\n", 1);
		get_status()->error = 1;
		return ;
	}
	close(fd);
}

void	create_or_update(char *filename)
{
	int	fd;

	fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (!fd)
	{
		ft_putstr_fd("Ambiguous redirect\n", 1);
		get_status()->error = 1;
		return ;
	}
	close(fd);
}

void	create_redirection_file(char *redirect_pos)
{
	char			buf[512];
	char			*substr[2];
	t_redirect_type	type;

	ft_memset(buf, 0, 512);
	type = redirect_type(redirect_pos);
	rarg_substring(substr, redirect_pos);
	ft_slice_cpy(buf, substr[0], substr[1]);
	if (type == R_DOUBLE_OUT)
		create_or_update(buf);
	else if (type == R_SINGLE_OUT)
		create_or_clean(buf);
}
