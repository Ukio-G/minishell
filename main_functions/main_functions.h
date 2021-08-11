/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:59:02 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 12:04:04 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_FUNCTIONS_H
# define MAIN_FUNCTIONS_H

# include <stdio.h>
# include "rl/readline.h"
# include "rl/history.h"
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include "fcntl.h"
# include <errno.h>
# include <signal/signal.h>
# include <errors_printer/error_printer.h>
# include "shell_status/shell_status.h"
# include "command.h"
# include "env_utils.h"
# include "file_utils.h"
# include "basic_shell.h"
# include "pipes/pipes.h"
# include "processes/processes.h"
# include "preprocessor/preprocessor.h"

enum e_history_error_code
{
	SUCCESS = 0,
	NO_HOME_PATH = 1,
	NO_HISTORY_FILE = 2
};

char			*process_input(char *raw_input);
t_ft_vector		create_process_info_set(t_ft_vector commands_text);
t_process_info	create_process_info(char *command);
int				update_history(char *line);
int				setup_history(void);
void			startup_init(char **argv, char **envp);
void			input_loop(void);
void			process_commands(char *line);
t_ft_vector		create_process_string_set(char *processed_input);

#endif
