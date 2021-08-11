/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:48:04 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 11:20:42 by atawana          ###   ########.fr       */
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

void	create_process_set(t_ft_vector process_info_set)
{
	t_process_info	*info;

	while (ft_vector_iter(&process_info_set))
	{
		info = ft_vector_iter_value(&process_info_set);
		info->pid = new_process(*info);
	}
}

void	wait_all_processes(t_ft_vector process_info_set)
{
	t_process_info	*info;

	while (ft_vector_iter(&process_info_set))
	{
		info = ft_vector_iter_value(&process_info_set);
		close_all_pipes();
		if (info->pid > 0)
		{
			waitpid(info->pid, &info->exit_code, 0);
			if (WIFEXITED(info->exit_code))
				get_status()->return_code = WEXITSTATUS(info->exit_code);
		}
	}
	close_redirects();
}

void	process_execve_errno(t_process_info *info)
{
	if (errno == EACCES)
	{
		info->error = E_FILE_NO_PERMISSION;
		print_error(E_FILE_NO_PERMISSION, info->original_cmd_str);
	}
}

pid_t	new_process(t_process_info info)
{
	pid_t	new_pid;

	if (!start_redirection())
		return (0);
	if (is_nonforkable(info))
	{
		get_status()->return_code = exec_builtin(&info);
		return (0);
	}
	new_pid = fork();
	if (new_pid == 0)
	{
		pipes_replace(info);
		if (!info.is_builtin)
		{
			execve(info.bin_path, info.argv, info.envp);
			if (info.error == NO_ERROR)
				process_execve_errno(&info);
			exit(code_from_error(info.error));
		}
		else
			exit(exec_builtin(&info));
	}
	return (new_pid);
}

t_process_info	new_process_info(char *path, char **argv, char **envp)
{
	t_process_info	result;

	result.in_d = NOT_SET;
	result.out_d = NOT_SET;
	result.in_d = NOT_SET;
	result.out_d = NOT_SET;
	result.is_builtin = is_builtin(path);
	result.error = is_correct_executable(path);
	result.bin_path = path;
	result.argv = preprocess_arguments(argv);
	result.envp = envp;
	return (result);
}
