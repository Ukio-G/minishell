#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <printf.h>
#include <signal.h>
#include <stdio.h>
#include "../command.h"
#include "processes.h"
#include "../shell_status.h"
#include "../pipes/pipes.h"
#include "../preprocessor/preprocessor.h"

void print_process(t_process_info info)
{
	printf("bin %s %i, in %d, out %d\n", info.bin_path, (int)info.pid ,info.in_d, info.out_d);
}


void create_process_set(t_ft_vector process_info_set)
{
	t_process_info *info;
	printf("process_info_set size %i\n", process_info_set.size);
	while (ft_vector_iter(&process_info_set))
	{
		info = ft_vector_iter_value(&process_info_set);
		info->pid = new_process(*info);
#ifdef DEBUG_PRINT
		print_process(*info);
#endif
	}
}

void wait_all_processes(t_ft_vector process_info_set)
{
	t_process_info *info;
	while (ft_vector_iter(&process_info_set))
	{
		info = ft_vector_iter_value(&process_info_set);
		close_all_pipes();
		waitpid(info->pid, &info->exit_code, 0);
	}
}

pid_t new_process(t_process_info info)
{
	pid_t new_pid = fork();

	if (new_pid == 0)
	{
		if (info.in_d != NOT_SET)
		{
			dup2(info.in_d, STDIN_FILENO);
		}
		if (info.out_d != NOT_SET)
		{
			dup2(info.out_d, STDOUT_FILENO);
		}
		close_all_pipes();
		execve(info.bin_path, info.argv, info.envp);
	}

	return new_pid;
}

void stop_all_processes(t_ft_vector process_info_set)
{
	t_process_info *info;

	while (ft_vector_iter(&process_info_set))
	{
		info = ft_vector_iter_value(&process_info_set);
		if (info->pid > 0)
		{
			kill(info->pid, SIGKILL);
		}
	}
}

t_process_info new_process_info(char *path, char **argv, char **envp)
{
	t_process_info result;
	result.bin_path = path;
	result.argv = preprocess_arguments(argv);
	result.envp = envp;
	result.in_d = NOT_SET;
	result.out_d = NOT_SET;
	return result;
}