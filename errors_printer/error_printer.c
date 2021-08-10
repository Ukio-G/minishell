#include <printf.h>
#include <libft.h>
#include <shell_status.h>
#include "error_printer.h"
#include "file_utils.h"

void print_error(t_executable_file_error file, char *path)
{
	if (file == E_FILE_IS_DIRECTORY)
	{
		printf("minishell: %s is a directory\n", path);
	}
	if (file == E_FILE_CMD_NOT_FOUND)
	{
		printf("minishell: %s command not found\n", path);
	}
	if (file == E_FILE_FILE_NOT_FOUND)
	{
		printf("minishell: %s No such file or directory\n", path);
	}
	if (file == E_FILE_NO_PERMISSION)
	{
		printf("minishell: %s Permission denied\n", path);
	}
}

int code_from_error(t_executable_file_error file)
{
	if (file == E_FILE_NO_PERMISSION || file == E_FILE_IS_DIRECTORY)
		return 126;
	if (file == E_FILE_CMD_NOT_FOUND || file == E_FILE_FILE_NOT_FOUND)
		return 127;
	return 0;
}

void print_pipe_error()
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 1);
	get_status()->return_code = 258;
}

void print_dot_error()
{
	ft_putstr_fd("minishell: .: filename argument required\n", 1);
	ft_putstr_fd(".: usage: . filename [arguments]\n", 1);
	get_status()->return_code = 2;
}
