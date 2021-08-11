/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:18:03 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 11:21:42 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <printf.h>
#include <signal.h>
#include <stdio.h>
#include <file_utils.h>
#include <errno.h>
#include <errors_printer/error_printer.h>
#include <env_utils.h>
#include "../command.h"
#include "processes.h"
#include "shell_status/shell_status.h"
#include "../pipes/pipes.h"
#include "../preprocessor/preprocessor.h"

int	is_nonforkable(t_process_info info)
{
	if (info.is_builtin && (ft_strncmp(info.bin_path, "cd", 3) == 0
			|| (ft_strncmp(info.bin_path, "exit", 5) == 0)
			|| (ft_strncmp(info.bin_path, "unset", 6) == 0)))
		return (1);
	return (0);
}
