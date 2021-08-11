/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:46:06 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:06:41 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_utils.h"
#include "libft.h"
#include "file_utils.h"
#include "permission.h"
#include <basic_shell.h>
#include <printf.h>

char	*make_abs_path(char *path, char *filename)
{
	char	*result;
	size_t	path_size;
	size_t	filename_size;

	path_size = ft_strlen(path);
	filename_size = ft_strlen(filename);
	result = malloc(path_size + filename_size + 2);
	if (!result)
		return (0);
	ft_memcpy(result, path, path_size);
	result[path_size] = '/';
	ft_memcpy(result + path_size + 1, filename, filename_size);
	result[path_size + filename_size + 1] = '\0';
	return (result);
}

char	*is_bin_in_env(char *binary_name)
{
	char	*path;
	char	**path_splitted;
	int		i;
	char	*abs_path;

	path = find_env_by_key("PATH");
	if (!path)
		return (0);
	path_splitted = ft_split(path, ':');
	free(path);
	i = 0;
	while (path_splitted[i])
	{
		abs_path = make_abs_path(path_splitted[i++], binary_name);
		if (abs_path)
		{
			if (is_file_exist(abs_path))
				return (abs_path);
			free(abs_path);
		}
		else
			exit(123);
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_process_info *info)
{
	char	*cmd;

	cmd = info->bin_path;
	if (ft_strncmp("echo", cmd, 5) == 0)
		return (echo(info));
	if (ft_strncmp("cd", cmd, 3) == 0)
		return (cd(info));
	if (ft_strncmp("unset", cmd, 6) == 0)
		return (unset(info));
	if (ft_strncmp("pwd", cmd, 4) == 0)
		return (pwd());
	if (ft_strncmp("env", cmd, 4) == 0)
		return (env());
	if (ft_strncmp("export", cmd, 7) == 0)
		return (export(info));
	if (ft_strncmp("exit", cmd, 5) == 0)
		ft_exit();
	return (0);
}

char	*make_bin_path(char *input)
{
	char	buffer[1024];
	char	*result;

	if (ft_strncmp(input, "./", 2) == 0)
	{
		ft_memset(buffer, 0, 1024);
		getcwd(buffer, 1024);
		result = ft_calloc(1, ft_strlen(buffer) + 2 + ft_strlen(input + 2));
		ft_memcpy(result, buffer, ft_strlen(buffer));
		result[ft_strlen(buffer)] = '/';
		ft_memcpy(result + ft_strlen(result), input + 2, ft_strlen(input + 2));
		return (result);
	}
	else if (ft_strncmp(input, "/", 1) == 0 || is_builtin(input))
		return (ft_strdup(input));
	else
		return (is_bin_in_env(input));
}
