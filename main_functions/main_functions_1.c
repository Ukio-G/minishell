/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 12:00:19 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 12:07:22 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_functions.h"

t_ft_vector	create_process_string_set(char *processed_input)
{
	t_ft_vector	result;
	char		**splitted_by_pipe;

	splitted_by_pipe = ft_split(processed_input, SPECIAL_PIPE);
	ft_vector_init(&result, sizeof(char *));
	if (!splitted_by_pipe)
	{
		printf("Malloc error\n");
		exit(1);
	}
	while (*splitted_by_pipe)
	{
		ft_vector_add(&result, splitted_by_pipe);
		splitted_by_pipe++;
	}
	return (result);
}

void	process_commands(char *line)
{
	get_status()->processed_input = process_input(line);
	get_status()->process_string_set = create_process_string_set(get_status
		()->processed_input);
	get_status()->pipes_set = create_pipes_set(get_status
		()->process_string_set);
	get_status()->process_info_set = create_process_info_set(get_status
		()->process_string_set);
	bind_process_with_pipes(get_status()->process_info_set, get_status
		()->pipes_set);
	create_process_set(get_status()->process_info_set);
	wait_all_processes(get_status()->process_info_set);
	update_env("?", ft_itoa(get_status()->return_code));
}

void	input_loop(void)
{
	char	*line;
	char	*trimmed;

	get_status()->fd_wt = dup(1);
	get_status()->fd_rt = dup(0);
	line = readline("Readline: ");
	get_status()->raw_input = line;
	if (line == 0)
	{
		ctrl_d_handler();
		return ;
	}
	else
	{
		if (*line == 0)
			return ;
		trimmed = ft_strtrim(line, " \t\n");
		if (ft_strlen(trimmed) != 0)
		{
			update_history(line);
			process_commands(line);
		}
		free(line);
		free(trimmed);
	}
}

void	startup_init(char **argv, char **envp)
{
	s_init();
	init_status(argv, copy_env(envp));
	setup_history();
	update_env("?", "0");
}
