#include <shell_status.h>
#include <readline/readline.h>
#include <sys/fcntl.h>
#include "redirection.h"

void redirect_from_heredoc()
{
	char *filename;

	filename = get_status()->redirect.in_filename;
	get_status()->redirect.in_fd = open(filename, O_RDONLY, 0644);
	dup2(get_status()->redirect.in_fd, 0);
}

void heredoc_read_loop()
{
	char *line;
	char *heredoc_delimiter;
	heredoc_delimiter = get_status()->redirect.in_delimiter;
	while (1)
	{
		line = readline("heredoc >");
		if (ft_strncmp(line, heredoc_delimiter, ft_strlen(line) + 1) == 0)
		{
			free(line);
			break;
		}
		write(get_status()->redirect.in_fd, line, ft_strlen(line));
		write(get_status()->redirect.in_fd, "\n", 1);
		free(line);
	}
	close(get_status()->redirect.in_fd);
}

void create_heredoc()
{
	char *filename;

	filename = ".heredoc";
	get_status()->redirect.in_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	get_status()->redirect.in_filename = filename;
}