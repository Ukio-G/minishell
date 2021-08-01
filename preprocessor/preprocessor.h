#ifndef MINISHELL_PREPROCESSOR_H
# define MINISHELL_PREPROCESSOR_H

# define SPECIAL_PIPE 0x01
# define SPECIAL_ARGS_DELIMITER 0x02

typedef enum	e_preprocessor_mode
{
	NO_MODE, SOFT_MODE, HARD_MODE
}				t_preprocessor_mode;

char			*preprocess(char *raw_input);
char			*preprocess_spaces(char *source);
char			*preprocess_pipes(char *source);
int				is_escaped(char *char_ptr, char *start_str, char* escape_chars);


#endif
