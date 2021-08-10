#include "shell_status.h"
#include "env_utils.h"
#include "libft.h"
#include "file_utils.h"
#include "permission.h"
#include <sys/stat.h>
#include <basic_shell.h>

char *make_abs_path(char* path, char* filename)
{
	char *result;
	size_t path_size;
	size_t filename_size;

	path_size = ft_strlen(path);
	filename_size = ft_strlen(filename);
	result = malloc( path_size + filename_size + 2);
	if (!result)
	{
		return 0;
	}
	ft_memcpy(result, path, path_size);
	result[path_size] = '/';
	ft_memcpy(result + path_size + 1, filename, filename_size);
	result[path_size + filename_size + 1] = '\0';
	return result;
}

char* is_bin_in_env(char *binary_name)
{
	char * path = find_env_by_key("PATH");
	if (!path)
	{
		return 0;
	}
	char **path_splitted = ft_split(path, ':');
	free(path);

	int i = 0;
	while (path_splitted[i])
	{
		char *abs_path = make_abs_path(path_splitted[i], binary_name);
		if (abs_path)
		{
			if (is_file_exist(abs_path) && current_user_permissions(abs_path).execute)
			{
				return abs_path;
			}
			free(abs_path);
			i++;
		}
		else
		{
			exit(123);
		}
	}
	return 0;
}

int is_builtin(char *cmd)
{
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		return 1;
	if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		return 1;
	if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		return 1;
	if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		return 1;
	if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		return 1;
	if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		return 1;
	if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		return 1;
	return 0;
}

void exec_builtin(t_process_info *info)
{
	char *cmd;

	cmd = info->bin_path;
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		echo(info);
	if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		cd(info);
	if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		unset(info);
	if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		pwd();
	if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		env();
	if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		export(info);
	if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		ft_exit();
}

char *make_bin_path(char * input)
{
	char buffer[1024];
	char * result;

	if (ft_strncmp(input, "./", 2) == 0)
	{
		getcwd(buffer, 1024);
		result = malloc(ft_strlen(buffer) + 2 + ft_strlen(input + 2));
		ft_memcpy(result, buffer, ft_strlen(buffer));
		result[ft_strlen(buffer)] = '/';
		ft_memcpy(result, input + 2, ft_strlen(input + 2));
		result[ft_strlen(buffer) + 2 + ft_strlen(input + 2)] = 0;
	}
	else if (ft_strncmp(input, "/", 1) == 0 || is_builtin(input))
		return ft_strdup(input);
	else
		return is_bin_in_env(input);
	return 0;
}

int bin_check(char * path)
{
	// Try to execute dir

	// No execute permission

	// Try to execute "./"

	// Symlinks?
	return 0;
}
