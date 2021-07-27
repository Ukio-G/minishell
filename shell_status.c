#include "shell_status.h"
#include "env.h"

t_shell_status *init_status(char **argv, char **envp)
{
	static t_shell_status status;
	if (argv && envp)
	{
		status.argv = argv;
		status.envp = envp;
		if (status.home)
		{
			free(status.home);
		}
		status.home = find_env_by_key("HOME");
		status.uid = 1000;
		status.gid = 1000;
	}
	return &status;
}

t_shell_status *get_status()
{
	return init_status(0, 0);
}
