#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "fcntl.h"
#include <errno.h>
#include "shell_status.h"
#include "command.h"
#include "env.h"
#include "file_utils.h"


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

void process_command(char * line)
{
	char **processed_input = ft_split(line, ' ');
	t_process_info info;
	int tokens = ft_split_count(processed_input);
	if (tokens > 0)
	{
		info.bin_path = make_bin_path(processed_input[0]);
		if (info.bin_path)
		{
			//TODO: bin_check(info.bin_path);
			info.argv = processed_input;
			info.envp = get_status()->envp;
			new_process(info);
		}
	}
	ft_split_free(processed_input);
}

void input_loop()
{
	char *line = readline("Readline: ");
	if (line == 0) {
		return;
	} else {
		char * trimmed = ft_strtrim(line, " \t\n");
		if (ft_strlen(trimmed) != 0) {
			update_history(line);
			rl_redisplay();
			process_command(line);
		}
		free(line);
		free(trimmed);
	}
}

void init_signals()
{

}

int main(int argc, char ** argv, char **envp)
{
	init_signals();
	init_status(argv, envp);
	setup_history();

    while (1) {
		input_loop();
    }


    free(get_status()->home);

	return 0;
}
