/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 17:42:55 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/07 20:44:07 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "basic_shell.h"

void	free_current_and_old_path(char *current_path, char *old_path)
{
	if (current_path)
		free(current_path);
	if (old_path)
		free(old_path);
	return ;
}

static void	pr_and_ret(char *msg, char *current_path, char *old_path)
{
	if (current_path)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(current_path, 1);
	}
	ft_putstr_fd(msg, 1);
	free_current_and_old_path(current_path, old_path);
	return ;
}

static void	change_and_update(char *current_path, char *old_path)
{
	if (!current_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		return;
	}
	chdir(current_path);
	update_env("PWD", current_path);
	update_env("OLDPWD", old_path);
	free_current_and_old_path(current_path, old_path);
	return ;
}

void	cd(char **argv)
{
	char		*current_path;
	char		*old_path;
	struct stat	s;
	mode_t		mode;

	if (get_2d_array_size(argv) > 2)
		return (pr_and_ret("minishell: cd: too many arguments\n",0, 0));
	old_path = find_env_by_key("PWD");
	if (get_2d_array_size(argv) == 1 || (ft_strncmp("--", argv[1],
				ft_strlen(argv[1])) == 0))
	{
		current_path = find_env_by_key("HOME");
		return (change_and_update(current_path, old_path));
	}
	if (process_path(argv, &current_path) == -1)
		return (pr_and_ret(0, current_path, old_path));
	if (stat(current_path, &s) == -1)
		return (pr_and_ret(": No such file or directory\n", current_path,
				old_path));
	mode = (s.st_mode >> (3 * 4)) << (3 * 4);
	if (mode != S_IFDIR)
		return (pr_and_ret(": Not a directory\n", current_path, old_path));
	return (change_and_update(current_path, old_path));
}
