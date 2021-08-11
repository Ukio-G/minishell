/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 03:00:51 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:05:31 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_utils.h"

t_executable_file_error	is_correct_executable(char *cmd)
{
	if (*cmd == 0)
		return (E_FILE_CMD_NOT_FOUND);
	if (is_builtin(cmd))
		return (E_FILE_NO_ERROR);
	if (*cmd == '.' || *cmd == '/')
	{
		if (is_directory(cmd))
			return (E_FILE_IS_DIRECTORY);
		if (!is_file_exist(cmd))
			return (E_FILE_FILE_NOT_FOUND);
	}
	else
	{
		if (!is_bin_in_env(cmd))
			return (E_FILE_CMD_NOT_FOUND);
	}
	return (E_FILE_NO_ERROR);
}
