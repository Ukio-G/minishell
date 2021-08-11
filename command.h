/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:08:33 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 12:08:48 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "stdlib.h"
# include <unistd.h>
# include "executable_file_error.h"

typedef struct s_process_info
{
	char					*bin_path;
	char					*original_cmd_str;
	char					**argv;
	char					**envp;
	int						in_d;
	int						out_d;
	pid_t					pid;
	int						exit_code;
	int						is_builtin;
	t_executable_file_error	error;
}	t_process_info;

#endif
