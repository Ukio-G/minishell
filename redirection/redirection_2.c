/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:25:40 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 11:30:05 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <file_utils.h>
#include <errors_printer/error_printer.h>
#include "redirection.h"
#include "shell_status/shell_status.h"
#include "preprocessor/preprocessor.h"

void	set_input_redirection(char *redirection)
{
	t_redirect_type	type;
	char			*argument;

	type = redirect_type(redirection);
	get_status()->redirect.input_type = type;
	argument = redirection_argument_new(redirection);
	if (type == R_DOUBLE_INPUT)
	{
		get_status()->redirect.in_delimiter = argument;
	}
	else if (type == R_SINGLE_INPUT)
	{
		get_status()->redirect.in_filename = argument;
	}
}

void	set_output_redirection(char *redirection)
{
	t_redirect_type	type;
	char			*argument;

	type = redirect_type(redirection);
	get_status()->redirect.output_type = type;
	argument = redirection_argument_new(redirection);
	get_status()->redirect.out_filename = argument;
}

void	start_out_redirect(t_redirect_type type)
{
	char	*filename;

	if (type == R_SINGLE_OUT)
	{
		filename = get_status()->redirect.out_filename;
		get_status()->redirect.out_fd = open(filename, O_WRONLY
			| O_TRUNC | O_CREAT, 0644);
		dup2(get_status()->redirect.out_fd, 1);
	}
	else if (type == R_DOUBLE_OUT)
	{
		filename = get_status()->redirect.out_filename;
		get_status()->redirect.out_fd = open(filename, O_APPEND
			| O_WRONLY | O_CREAT, 0644);
		dup2(get_status()->redirect.out_fd, 1);
	}
}

void	start_input_redirect(t_redirect_type type)
{
	char	*filename;

	if (type == R_SINGLE_INPUT)
	{
		filename = get_status()->redirect.in_filename;
		get_status()->redirect.in_fd = open(filename, O_RDONLY, 0644);
		dup2(get_status()->redirect.in_fd, 0);
	}
	else if (type == R_DOUBLE_INPUT)
	{
		create_heredoc();
		heredoc_read_loop();
		redirect_from_heredoc();
	}
}

int	start_redirection(void)
{
	t_redirect_type	output_type;
	t_redirect_type	input_type;

	output_type = get_status()->redirect.output_type;
	input_type = get_status()->redirect.input_type;
	if (input_type != R_NO_TYPE)
	{
		if (!is_file_exist(get_status()->redirect.in_filename))
		{
			print_input_redirect_error(get_status()->redirect.in_filename);
			return (0);
		}
		start_input_redirect(input_type);
	}
	if (output_type != R_NO_TYPE)
		start_out_redirect(output_type);
	return (1);
}
