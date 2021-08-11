/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:46:23 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:12:14 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_UTILS_H
# define FILE_UTILS_H
# include "command.h"

int						is_file_exist(char *filename);
char					*is_bin_in_env(char *binary_name);
char					*make_abs_path(char *path, char *filename);
char					*make_bin_path(char *input);
int						is_builtin(char *cmd);
int						exec_builtin(t_process_info *info);
t_executable_file_error	is_correct_executable(char *cmd);
int						is_directory(char *path);

#endif
