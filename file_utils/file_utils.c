/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:46:18 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:11:07 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "permission.h"
#include "shell_status/shell_status.h"
#include <sys/stat.h>
#include <fcntl.h>

int	is_file_exist(char *filename)
{
	struct stat	s;

	return (stat(filename, &s) == 0);
}

int	is_directory(char *path)
{
	struct stat	s;
	mode_t		mode;

	if (!is_file_exist(path))
		return (0);
	stat(path, &s);
	mode = (s.st_mode >> (3 * 4)) << (3 * 4);
	if (mode == S_IFDIR)
		return (1);
	return (0);
}
