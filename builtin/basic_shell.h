/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_shell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:55:27 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 02:56:20 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASIC_SHELL_H
# define BASIC_SHELL_H

# include "libft.h"
# include "env_utils.h"
# include <sys/stat.h>
# include "shell_status/shell_status.h"

size_t	get_2d_array_size(char **array);
int		find_number_of_key(char *key);
int		echo(t_process_info *info);
int		cd(t_process_info *info);
int		process_path(char **argv, char **current_path);
int		pwd(void);
int		export(t_process_info *info);
int		unset(t_process_info *info);
int		env(void);
void	ft_exit(void);

#endif
