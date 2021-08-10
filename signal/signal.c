#include <sys/wait.h>
#include <stddef.h>
#include <libft.h>
#include "signal.h"
#include "readline/readline.h"

void	s_ctrl_slash(void)
{
	int pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (!pid)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
	}
	else
	{
		ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void	s_ctrl_c(void)
{
	int pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (pid)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		write(1, "\n", 1);
		rl_replace_line("\0", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (!pid)
	{

	}
}

void	ctrl_d_handler(void)
{
//	ft_putstr_fd("\b\b  ", 1);
	write(1, "exit\n", 5);
	exit(0);
}

void s_init()
{
	signal(SIGQUIT, (void *)s_ctrl_slash);
	signal(SIGINT, (void *)s_ctrl_c);
}
