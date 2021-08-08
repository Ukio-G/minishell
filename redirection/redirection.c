/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:03:36 by atawana           #+#    #+#             */
/*   Updated: 2021/08/08 15:17:59 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	redirect->out_fd = -1;
	redirect->in_fd = -1;
	redirect->str_ptr = 0;
	redirect->delimiter = 0;
	redirect->filename = 0;
	redirect->input_type = R_NO_TYPE;
	redirect->output_type = R_NO_TYPE;
}

void	determinate_redirections(char *preprocessed_input)
{
	char *redirect_position;
	t_redirect_type tmp_type;
	t_redirect result;

	init_redirection(&result);
	redirect_position = ft_strpbrk2(preprocessed_input, "><");
	while (redirect_position)
	{
		if (!is_escaped(redirect_position, preprocessed_input, "\"\'"))
		{
			tmp_type = redirect_type(redirect_position);
			result.str_ptr = redirect_position;
			if (tmp_type == R_DOUBLE_INPUT)
				redirection_delimiter(&result);
			if (tmp_type == R_SINGLE_OUT || tmp_type == R_DOUBLE_OUT)
				redirection_filename(&result);
		}
		redirect_position = ft_strpbrk2(preprocessed_input, "><");
	}
}

void redirection_file_descriptor(t_redirect *p_redirect)
{

}

void redirection_filename(t_redirect *p_redirect)
{

}

void redirection_delimiter(t_redirect *p_redirect)
{

}
