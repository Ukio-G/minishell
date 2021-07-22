#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"
#include "fcntl.h"

#define HISTORY_PATH "/home/dinara/.minishell-history"


char * find_env_by_key(char **envp, char * str)
{
    char * result = 0;
    while (envp && !result) {
        char ** pair = ft_split(*envp, '=');
        if (ft_strncmp(pair[0], str, ft_strlen(str)) == 0) {
            result = ft_strdup(pair[1]);
            ft_splitline_free(pair);
        }
        envp++;
    }
    return result;
}

//char * history_path
enum HISTORY_ERROR_CODE {
    SUCCESS = 0, NO_HOME_PATH = 1, NO_HISTORY_FILE = 2
};
int setup_history(char *home_path) {

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

#include <errno.h>

int update_history(char *home_path, char *line) {
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
    int retval = write(fd, line, ft_strlen(line));
    if (retval < 0)
        printf("%s", strerror(errno));
    retval = write(fd, "\n", 1);
    if (retval < 0)
        printf("%s", strerror(errno));
    free(history_file_path);
    close(fd);
    return SUCCESS;
}



int main(int argc, char ** argv, char **envp)
{

    char* home_path = find_env_by_key(envp, "HOME");
    setup_history(home_path);

    while (1) {
        char *line = readline("Readline: ");
        if (line == 0) {
            break;
        } else {
            char * trimmed = ft_strtrim(line, " \t\n");
            if(ft_strlen(trimmed) != 0) {
                update_history(home_path, line);
                rl_redisplay();
            }
            printf("|%s|\n", rl_line_buffer);
            free(line);
        }
    }

    free(home_path);

	return 0;
}
