/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:45:59 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 02:59:25 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_PRINTER_H
# define ERROR_PRINTER_H

# include "file_utils.h"
# define MINISHELL_MEMORY_ERROR 250

void	print_error(t_executable_file_error file, char *path);
int		code_from_error(t_executable_file_error file);
void	print_pipe_error(void);
void	print_dot_error(void);

#endif
