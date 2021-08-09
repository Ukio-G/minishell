/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:03:36 by atawana           #+#    #+#             */
/*   Updated: 2021/08/09 17:16:13 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <readline/readline.h>
#include "redirection.h"
#include "shell_status.h"
#include "preprocessor/preprocessor.h"



t_redirect_type redirect_type(char *start_position)
{
	if (*start_position == '>')
	{
		if (start_position[1] == '>')
			return R_DOUBLE_OUT;
		else
			return R_SINGLE_OUT;
	}
	else if (*start_position == '<')
	{
		if (start_position[1] == '<')
			return  R_DOUBLE_INPUT;
		else
			return R_SINGLE_INPUT;
	}
	return 0;
}

void	init_redirection(t_redirect *redirect)
{
	ft_memset(redirect, 0, sizeof(t_redirect));
	redirect->out_fd = -1;
	redirect->in_fd = -1;
	redirect->input_type = R_NO_TYPE;
	redirect->output_type = R_NO_TYPE;
}

void create_or_clean(char *filename)
{

	int fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (!fd)
	{
		ft_putstr_fd("Ambiguous redirect\n", 1);
		get_status()->error = 1;
		return;
	}
	close(fd);
}

void create_or_update(char *filename)
{
	int fd;

	fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (!fd)
	{
		ft_putstr_fd("Ambiguous redirect\n", 1);
		get_status()->error = 1;
		return;
	}
	close(fd);
}

void create_redirection_file(char* redirect_pos)
{
	char buf[512];
	char *substr[2];
	t_redirect_type type;

	type = redirect_type(redirect_pos);
	rarg_substring(substr, redirect_pos);
	ft_slice_cpy(buf, substr[0], substr[1]);
	if (type == R_DOUBLE_OUT)
		create_or_update(buf);
	else if (type == R_SINGLE_OUT)
		create_or_clean(buf);
}

void set_input_redirection(char *redirection)
{
	t_redirect_type type;
	char * argument;

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

void set_output_redirection(char *redirection)
{
	t_redirect_type type;
	char * argument;

	type = redirect_type(redirection);
	get_status()->redirect.output_type = type;
	argument = redirection_argument_new(redirection);
	get_status()->redirect.out_filename = argument;
}

void start_out_redirect(t_redirect_type type)
{
	char *filename;
	if (type == R_SINGLE_OUT)
	{
		filename = get_status()->redirect.out_filename;
		get_status()->redirect.out_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(get_status()->redirect.out_fd, 1);
	}
	else if (type == R_DOUBLE_OUT)
	{
		filename = get_status()->redirect.out_filename;
		get_status()->redirect.out_fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
		dup2(get_status()->redirect.out_fd, 1);
	}
}

void close_redirects()
{
	t_redirect_type output_type;
	t_redirect_type input_type;

	output_type = get_status()->redirect.output_type;
	input_type = get_status()->redirect.input_type;
	if (output_type != R_NO_TYPE)
		close(get_status()->redirect.out_fd);
	if (input_type != R_NO_TYPE)
		close(get_status()->redirect.in_fd);
}

void start_input_redirect(t_redirect_type type)
{
	if (type == R_SINGLE_INPUT)
	{
		get_status()->redirect.in_fd = open(get_status()->redirect.in_filename, O_RDONLY, 0644);
		dup2(get_status()->redirect.in_fd, 0);
	}
	else if (type == R_DOUBLE_INPUT)
	{
//		create_heredoc();
//		redirect_from_heredoc();
	}
}

void start_redirection()
{
	t_redirect_type output_type;
	t_redirect_type input_type;

	output_type = get_status()->redirect.output_type;
	input_type = get_status()->redirect.input_type;
	if (output_type != R_NO_TYPE)
		start_out_redirect(output_type);
	if (input_type != R_NO_TYPE)
		start_input_redirect(input_type);
}

void set_status_redirection(char *redir[3])
{
	if (redir[LAST_IN])
		set_input_redirection(redir[LAST_IN]);
	if (redir[LAST_OUT])
		set_output_redirection(redir[LAST_OUT]);
}

