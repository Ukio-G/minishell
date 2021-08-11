/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:42:55 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/11 02:00:41 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "basic_shell.h"

int	biggest_len(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	return (len2);
}

void	free_current_and_old_path(char *current_path, char *old_path)
{
	if (current_path)
		free(current_path);
	if (old_path)
		free(old_path);
}

static int	pr_and_ret(char *msg, char *current_path, char *old_path)
{
	if (current_path)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(current_path, 1);
	}
	ft_putstr_fd(msg, 1);
	free_current_and_old_path(current_path, old_path);
	return (1);
}

static int	change_and_update(char *current_path, char *old_path)
{
	if (!current_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		return (1);
	}
	chdir(current_path);
	update_env("PWD", current_path);
	update_env("OLDPWD", old_path);
	free_current_and_old_path(current_path, old_path);
	return (0);
}

int	cd(t_process_info *info)
{
	char		*current_path;
	char		*old_path;
	struct stat	s;
	mode_t		mode;

	old_path = find_env_by_key("PWD");
	printf("LEAK %s:%i %p\n", __FILE__, __LINE__, old_path);

	if ((get_2d_array_size(info->argv) == 1) || (ft_strncmp("--", info->argv[1],
				biggest_len("--", info->argv[1])) == 0))
	{
		current_path = find_env_by_key("HOME");
		printf("LEAK %s:%i %p\n", __FILE__, __LINE__, current_path);
		return (change_and_update(current_path, old_path));
	}
	if (process_path(info->argv, &current_path) == -1)
	{
		free_current_and_old_path(current_path, old_path);
		return (1);
	}
	if (stat(current_path, &s) == -1)
		return (pr_and_ret(": No such file or directory\n", current_path,
				old_path));
	mode = (s.st_mode >> (3 * 4)) << (3 * 4);
	if (mode != S_IFDIR)
		return (pr_and_ret(": Not a directory\n", current_path, old_path));
	return (change_and_update(current_path, old_path));
}
