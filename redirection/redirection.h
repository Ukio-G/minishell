#ifndef REDIRECTION_H
#define REDIRECTION_H

typedef enum e_redirect_type
{
	R_NO_TYPE,
	R_SINGLE_OUT,
	R_DOUBLE_OUT,
	R_SINGLE_INPUT,
	R_DOUBLE_INPUT
} t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type input_type;
	t_redirect_type output_type;
	char *in_delimiter;
	char *out_filename;
	char *in_filename;
	int out_fd;
	int in_fd;
} t_redirect;

t_redirect_type redirect_type(char *start_position);
void	init_redirection(t_redirect *redirect);
void	set_status_redirection(char *redir[3]);
void	create_redirection_file(char* redirect_pos);
void	create_or_update(char *);
void	create_or_clean(char *);
//void	create_heredoc();
//void	redirect_from_heredoc();
void	start_redirection();
void close_redirects();
#endif
