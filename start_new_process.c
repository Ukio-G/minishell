#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "command.h"

void destroy_process_resourses(t_process_info info)
{
	free(info.bin_path);
}

int new_process(t_process_info info)
{
	pid_t new_pid = fork();
	int return_code;

	return_code = 0;
	if (new_pid == 0)
	{
		execve(info.bin_path, info.argv, info.envp);
	}
	else
	{
		waitpid(new_pid, &return_code, 0);
		return_code = (return_code << 24) >> 24;
	}
	destroy_process_resourses(info);
	return return_code;
}


t_process_info new_process_info(char *path, char **argv, char **envp)
{
	t_process_info result;
	result.bin_path = path;
	result.argv = argv;
	result.envp = envp;

	return result;
}