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
	char *delimiter;
	char *str_ptr;
	char *filename;
	int out_fd;
	int in_fd;
} t_redirect;

t_redirect_type redirect_type(char *start_position);
void redirection_delimiter(t_redirect *p_redirect);
void redirection_filename(t_redirect *p_redirect);
void redirection_file_descriptor(t_redirect *p_redirect);

#endif
