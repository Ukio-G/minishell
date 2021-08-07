#ifndef MINISHELL_PREPROCESSOR_H
# define MINISHELL_PREPROCESSOR_H

# define SPECIAL_PIPE 0x01
# define SPECIAL_ARGS_DELIMITER 0x02
# define VARIABLE_NAME 0
# define VARIABLE_VALUE 1
# define READ_POS 0
# define WRITE_POS 1
# define DOLLAR_POS 2


#ifdef DEBUG_PRINT
	#define DEBUG_PRINT_MACRO(...) printf (__VA_ARGS__)
#else
	#define DEBUG_PRINT_MACRO(...)
#endif

#define PREPROCESSOR_TEST_CASE(N, LINE) \
	result = preprocess(TEST_CASE_##N); \
	compare_string(result, TEST_CASE_RESULT_##N, LINE); \
	free(result);

#define PREPROCESSOR_LENGTH_TEST_CASE(N, LINE) \
	pipes = preprocess_pipes(TEST_CASE_##N); \
	spaces = preprocess_spaces(pipes); \
    length = expanded_string_length(spaces);   \
	printf("\nTest case %i: ", N); \
	compare_length(length, ft_strlen(TEST_CASE_RESULT_##N), __LINE__, TEST_CASE_##N); \
	free(pipes); \
	free(spaces);

typedef enum	e_preprocessor_mode
{
	NO_MODE, SOFT_MODE, HARD_MODE
}				t_preprocessor_mode;

char			*preprocess(char *raw_input);
char			*preprocess_spaces(char *source);
char			*preprocess_pipes(char *source);
int				is_escaped(char *char_ptr, char *start_str, char* escape_chars);
char			**preprocess_arguments(char **argv);
int 			expanded_string_length(char *source);

#endif
