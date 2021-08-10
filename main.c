#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "fcntl.h"
#include <errno.h>
#include <signal/signal.h>
#include <errors_printer/error_printer.h>
#include "shell_status.h"
#include "command.h"
#include "env_utils.h"
#include "file_utils.h"
#include "basic_shell.h"
#include "pipes/pipes.h"
#include "processes/processes.h"
#include "preprocessor/preprocessor.h"

enum HISTORY_ERROR_CODE {
    SUCCESS = 0, NO_HOME_PATH = 1, NO_HISTORY_FILE = 2
};

int setup_history() {
	char *home_path = get_status()->home;
    if (!home_path) {
        return NO_HOME_PATH;
    }
    char *history_file_path = ft_strjoin(home_path, "/.minishell");
    int fd = open(history_file_path, O_RDONLY);
    if (fd < 0) {
        free(history_file_path);
        return NO_HISTORY_FILE;
    }
    char *line;
    while (get_next_line(fd, &line))
    {
        add_history(line);
        free(line);
    }

    free(history_file_path);
    close(fd);
    return SUCCESS;
}

int update_history(char *line) {
	char *home_path = get_status()->home;
	add_history(line);
    if (!home_path) {
        return NO_HOME_PATH;
    }
    char *history_file_path = ft_strjoin(home_path, "/.minishell");
    int fd = open(history_file_path, O_WRONLY | O_APPEND | O_CREAT, 0777);
    if (fd < 0) {
        free(history_file_path);
        return NO_HISTORY_FILE;
    }
    write(fd, line, ft_strlen(line));
    write(fd, "\n", 1);
    free(history_file_path);
    close(fd);
    return SUCCESS;
}


t_process_info create_process_info(char * command)
{
	char **processed_input = ft_split(command, SPECIAL_ARGS_DELIMITER);
	char *bin_path;
	t_process_info info;
	int tokens = ft_split_count(processed_input);
	if (tokens > 0)
	{
		bin_path = preprocess_argument(processed_input[0]);
		free(processed_input[0]);
		processed_input[0] = bin_path;
		if (is_correct_executable(bin_path) == E_FILE_NO_ERROR)
			info = new_process_info(make_bin_path(bin_path), processed_input, get_status()->envp);
		else
		{
			print_error(is_correct_executable(bin_path), bin_path);
			info = new_process_info(bin_path, 0, 0);
		}
		ft_split_free(processed_input);
	}
	return info;
}

t_ft_vector create_process_info_set(t_ft_vector commands_text)
{
	t_process_info tmp;
	t_ft_vector result;

	ft_vector_init(&result, sizeof(t_process_info));
	while (ft_vector_iter(&commands_text))
	{
		tmp = create_process_info(*((char**)ft_vector_iter_value(&commands_text)));
		ft_vector_add(&result, &tmp);
	}
	return result;
}

char *process_input(char *raw_input)
{
	return preprocess(raw_input);
}

t_ft_vector create_process_string_set(char *processed_input)
{
	t_ft_vector result;
	char **splitted_by_pipe;

	splitted_by_pipe = ft_split(processed_input, SPECIAL_PIPE);
	ft_vector_init(&result, sizeof(char*));
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
	return result;
}

void update_return_code();

void process_commands(char * line)
{
	get_status()->processed_input = process_input(line);
	get_status()->process_string_set = create_process_string_set(get_status()->processed_input);

	get_status()->pipes_set = create_pipes_set(get_status()->process_string_set);
	get_status()->process_info_set = create_process_info_set(get_status()->process_string_set);
	bind_process_with_pipes(get_status()->process_info_set, get_status()->pipes_set);

	create_process_set(get_status()->process_info_set);
	wait_all_processes(get_status()->process_info_set);
	update_return_code();
}

void update_return_code()
{
	update_env("?", ft_itoa(get_status()->return_code));
}

void input_loop()
{
	char *line;

	get_status()->fd_wt = dup(1);
	get_status()->fd_rt = dup(0);
	line = readline("Readline: ");
	get_status()->raw_input = line;
	if (line == 0) {
		ctrl_d_handler();
		return;
	} else {
		if (*line == 0)
			return;
		char * trimmed = ft_strtrim(line, " \t\n");
		if (ft_strlen(trimmed) != 0) {
			update_history(line);
			process_commands(line);
		}
		free(line);
		free(trimmed);
	}
}

void test_preprocessor();

void startup_init(char ** argv, char **envp)
{
	s_init();
	init_status(argv, copy_env(envp));
	setup_history();
	update_env("?", "0");
#ifdef TEST_PREPROCESSOR
	test_preprocessor();
#endif
}

int main(int argc, char ** argv, char **envp)
{

	startup_init(argv, envp);
	while (1) {
		input_loop();
	}

	free(get_status()->home);
	return 0;
}
