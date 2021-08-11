/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_file_error.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:46:11 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:07:52 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTABLE_FILE_ERROR_H
# define EXECUTABLE_FILE_ERROR_H

typedef enum e_executable_file
{
	E_FILE_NO_ERROR,
	E_FILE_NO_PERMISSION,
	E_FILE_IS_DIRECTORY,
	E_FILE_CMD_NOT_FOUND,
	E_FILE_FILE_NOT_FOUND
}	t_executable_file_error;

#endif
