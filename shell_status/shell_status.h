/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_status.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:50:58 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 02:50:58 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SHELL_STATUS_H
#define MINISHELL_SHELL_STATUS_H

#include <stdlib.h>
#include <redirection/redirection.h>
#include "command.h"
#include "ft_vector/ft_vector.h"

typedef struct		s_shell_status
{
	char			**envp;
	char			**argv;
	char			*home;
	char			*raw_input;
	char			*processed_input;
	t_ft_vector		pipes_set;
	t_ft_vector		process_set;
	t_ft_vector		process_string_set;
	t_ft_vector		process_info_set;
	int				uid;
	int				gid;
	t_redirect		redirect;
	int 			error;
	int 			fd_wt;
	int 			fd_rt;
	int				return_code;
}					t_shell_status;


t_shell_status		*init_status(char **argv, char **envp);
t_shell_status		*get_status();
char 				*find_env_by_key(char * str);

#endif //MINISHELL_SHELL_STATUS_H
