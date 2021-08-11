/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:59:50 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 15:44:43 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_functions.h"

int	setup_history(void)
{
	char	*history_file_path;
	char	*home_path;
	int		fd;
	char	*line;

	home_path = get_status()->home;
	if (!home_path)
		return (NO_HOME_PATH);
	history_file_path = ft_strjoin(home_path, "/.minishell");
	fd = open(history_file_path, O_RDONLY);
	if (fd < 0)
	{
		free(history_file_path);
		return (NO_HISTORY_FILE);
	}
	while (get_next_line(fd, &line))
	{
		add_history(line);
		free(line);
	}
	free(history_file_path);
	close(fd);
	return (SUCCESS);
}

int	update_history(char *line)
{
	char	*home_path;
	char	*history_file_path;
	int		fd;

	home_path = get_status()->home;
	add_history(line);
	if (!home_path)
		return (NO_HOME_PATH);
	history_file_path = ft_strjoin(home_path, "/.minishell");
	fd = open(history_file_path, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd < 0)
	{
		free(history_file_path);
		return (NO_HISTORY_FILE);
	}
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(history_file_path);
	close(fd);
	return (SUCCESS);
}

t_process_info	create_process_info(char *command)
{
	t_executable_file_error	file_error;
	t_process_info			info;
	char					*original_name;
	char					**processed_input;

	if (ft_strncmp(command, ".", 2) == 0)
		return (new_process_info(".", 0, 0));
	processed_input = ft_split(command, SPECIAL_ARGS_DELIMITER);
	info.pid = 0;
	if (ft_split_count(processed_input) > 0)
	{
		original_name = preprocess_argument(processed_input[0]);
		file_error = is_correct_executable(original_name);
		if (file_error == E_FILE_NO_ERROR)
			info = new_process_info(make_bin_path(original_name),
					processed_input, get_status()->envp);
		else
		{
			print_error(file_error, original_name);
			info = new_process_info(original_name, 0, 0);
		}
		info.original_cmd_str = original_name;
	}
	ft_split_free(processed_input);
	return (info);
}

t_ft_vector	create_process_info_set(t_ft_vector commands_text)
{
	t_process_info	tmp;
	t_ft_vector		result;

	ft_vector_init(&result, sizeof(t_process_info));
	while (ft_vector_iter(&commands_text))
	{
		tmp = create_process_info(
				*((char **) ft_vector_iter_value(&commands_text)));
		if (tmp.error != E_FILE_IS_DIRECTORY)
			ft_vector_add(&result, &tmp);
	}
	return (result);
}

char	*process_input(char *raw_input)
{
	return (preprocess(raw_input));
}
