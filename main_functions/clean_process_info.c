/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_process_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:04:11 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 15:51:09 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_functions.h"

void	clean_process_info(t_process_info *info)
{
	if (info->bin_path)
		free(info->bin_path);
	if (info->original_cmd_str)
		free(info->original_cmd_str);
	if (info->argv)
		ft_split_free(info->argv);
}

void	clean_processes_info(void)
{
	char	*tmp;

	while (ft_vector_iter(&get_status()->process_info_set))
	{
		clean_process_info((t_process_info *) ft_vector_iter_value
			(&get_status()->process_info_set));
	}
	while (ft_vector_iter(&get_status()->process_string_set))
	{
		tmp = *(char **)ft_vector_iter_value(&get_status()->process_string_set);
		free(tmp);
		tmp = 0;
	}
	ft_vector_free(&get_status()->process_info_set);
	ft_vector_free(&get_status()->process_string_set);
	ft_vector_free(&get_status()->pipes_set);
	ft_vector_free(&get_status()->process_set);
	if (get_status()->redirect.out_filename)
		free(get_status()->redirect.out_filename);
	if (get_status()->redirect.in_filename)
		free(get_status()->redirect.in_filename);
	if (get_status()->redirect.in_delimiter)
		free(get_status()->redirect.in_delimiter);
}
