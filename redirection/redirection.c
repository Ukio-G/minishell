/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:03:36 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 11:28:37 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <file_utils.h>
#include <errors_printer/error_printer.h>
#include "redirection.h"
#include "shell_status/shell_status.h"
#include "preprocessor/preprocessor.h"

void	close_redirects(void)
{
	t_redirect_type	output_type;
	t_redirect_type	input_type;

	output_type = get_status()->redirect.output_type;
	input_type = get_status()->redirect.input_type;
	if (output_type != R_NO_TYPE)
	{
		close(get_status()->redirect.out_fd);
		dup2(get_status()->fd_wt, 1);
		close(get_status()->fd_wt);
	}
	if (input_type != R_NO_TYPE)
	{
		close(get_status()->redirect.in_fd);
		dup2(get_status()->fd_rt, 0);
		close(get_status()->fd_rt);
	}
}

void	set_status_redirection(char *redir[3])
{
	if (redir[LAST_IN])
		set_input_redirection(redir[LAST_IN]);
	if (redir[LAST_OUT])
		set_output_redirection(redir[LAST_OUT]);
}
