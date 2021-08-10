#ifndef MINISHELL_PREPROCESSOR_H
# define MINISHELL_PREPROCESSOR_H

# define SPECIAL_PIPE 0x01
# define SPECIAL_ARGS_DELIMITER 0x02
# define VARIABLE_NAME 0
# define VARIABLE_VALUE 1
# define READ_POS 0
# define WRITE_POS 1
# define DOLLAR_POS 2
# define LAST_OUT 0
# define LAST_IN 1
# define END_REDIRECTIONS_STRING 2

#ifdef DEBUG_PRINT
	#define DEBUG_PRINT_MACRO(...) printf (__VA_ARGS__)
#else
	#define DEBUG_PRINT_MACRO(...)
#endif

#define USER_MACRO "atawana"
#define HOME_MACRO "/Users/"

#define PREPROCESSOR_TEST_CASE(N, LINE) \
	result = preprocess(TEST_CASE_##N); \
	printf("\nTest case (preprocessing) %i: ", N); \
	compare_string(result, TEST_CASE_RESULT_##N, LINE); \
	free(result);

#define PREPROCESSOR_LENGTH_TEST_CASE(N, LINE) \
	pipes = preprocess_pipes(TEST_CASE_##N); \
	spaces = preprocess_spaces(pipes); \
    length = expanded_string_length(spaces);   \
	printf("\nTest case (length) %i: ", N); \
	compare_length(length, ft_strlen(TEST_CASE_RESULT_##N), __LINE__, TEST_CASE_##N); \
	free(pipes); \
	free(spaces);

#define REMOVE_STRING_SAMPLE "abcdefghijklmnop1234567890"

# define REMOVE_STRING_TEST_RESULT_1 "abcijklmnop1234567890"
# define REMOVE_STRING_TEST_RESULT_2 "efghijklmnop1234567890"
# define REMOVE_STRING_TEST_RESULT_3 "abcdefghijklmnop12345678"
# define REMOVE_STRING_TEST_RESULT_4 "abcdefghijklmnop123456789"
# define REMOVE_STRING_TEST_RESULT_5 "bcdefghijklmnop1234567890"
# define REMOVE_STRING_TEST_RESULT_6 "abcdefghijlmnop1234567890"

#define REMOVE_STRING_START_1 3
#define REMOVE_STRING_END_1 7

#define REMOVE_STRING_START_2 0
#define REMOVE_STRING_END_2 3

#define REMOVE_STRING_START_3 24
#define REMOVE_STRING_END_3 25

#define REMOVE_STRING_START_4 25
#define REMOVE_STRING_END_4 25

#define REMOVE_STRING_START_5 0
#define REMOVE_STRING_END_5 0

#define REMOVE_STRING_START_6 10
#define REMOVE_STRING_END_6 10

#define REMOVE_STRING_TEST_CASE(N, LINE) \
	preprocessed = ft_strdup(REMOVE_STRING_SAMPLE); \
	substring[0] =  preprocessed + REMOVE_STRING_START_##N; \
	substring[1] =   preprocessed + REMOVE_STRING_END_##N; \
	remove_substring(preprocessed, substring); \
	expected = REMOVE_STRING_TEST_RESULT_##N;       \
	printf("\nTest case (remove string) %i: ", N); \
	compare_removed_string(preprocessed, expected, LINE); \
	free(preprocessed);


# define TEST_FIND_REDIRECTION_SOURCE_1 "cat <filename"
# define TEST_FIND_REDIRECTION_SOURCE_2 "echo 123 >filename"
# define TEST_FIND_REDIRECTION_SOURCE_3 "cat <filename < file2"
# define TEST_FIND_REDIRECTION_SOURCE_4 "echo 123 >> filename >new_file >>correct_file"
# define TEST_FIND_REDIRECTION_SOURCE_5 "<123 <456 cat <filename < file2 >567 > 098"
# define TEST_FIND_REDIRECTION_SOURCE_6 "cat 1<content>234"
# define TEST_FIND_REDIRECTION_SOURCE_7 "cat 1<content>$USER/../"

# define TEST_FIND_LAST_REDIRECTION_OUT_1 (-1)
# define TEST_FIND_LAST_REDIRECTION_IN_1 (4)

# define TEST_FIND_LAST_REDIRECTION_OUT_2 (9)
# define TEST_FIND_LAST_REDIRECTION_IN_2 (-1)

# define TEST_FIND_LAST_REDIRECTION_OUT_3 (-1)
# define TEST_FIND_LAST_REDIRECTION_IN_3 (14)

# define TEST_FIND_LAST_REDIRECTION_OUT_4 (31)
# define TEST_FIND_LAST_REDIRECTION_IN_4 (-1)

# define TEST_FIND_LAST_REDIRECTION_OUT_5 (37)
# define TEST_FIND_LAST_REDIRECTION_IN_5 (24)

# define TEST_FIND_LAST_REDIRECTION_OUT_6 (13)
# define TEST_FIND_LAST_REDIRECTION_IN_6 (5)

# define TEST_FIND_LAST_REDIRECTION_OUT_7 (13)
# define TEST_FIND_LAST_REDIRECTION_IN_7 (5)

#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_1 0
#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_1 "filename"

#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_2 "filename"
#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_2 0

#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_3 0
#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_3 "file2"

#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_4 "correct_file"
#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_4 0

#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_5 "098"
#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_5 "file2"

#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_6 "234"
#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_6 "content"

#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_7 "" USER_MACRO "/../"
#define TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_7 "content"

#define TEST_FIND_LAST_REDIRECTION_CASE(N, LINE) \
	source = TEST_FIND_REDIRECTION_SOURCE_##N; \
	redirections[0] = 0; \
	redirections[1] = 0; \
	redirections[2] = 0; \
	pipes = preprocess_pipes(source); \
	spaces = preprocess_spaces(pipes); \
	variables = preprocess_variables(spaces); \
	find_last_redirection(redirections, variables); \
	printf("\nTest case (find last redirect) %i: ", N); \
	compare_last_find_redirection(redirections, variables, TEST_FIND_LAST_REDIRECTION_OUT_##N, TEST_FIND_LAST_REDIRECTION_IN_##N, LINE); \
	free (pipes); \
	free (spaces); \
	free (variables);

#define TEST_LAST_REDIRECTIONS_ARGUMENT(N, LINE) \
	source = TEST_FIND_REDIRECTION_SOURCE_##N; \
	redirections[0] = 0; \
	redirections[1] = 0; \
	redirections[2] = 0; \
	in = TEST_LAST_REDIRECTION_WITH_ARGUMENT_IN_##N; \
	out = TEST_LAST_REDIRECTION_WITH_ARGUMENT_OUT_##N; \
	pipes = preprocess_pipes(source); \
	spaces = preprocess_spaces(pipes); \
    variables = preprocess_variables(spaces); \
    find_last_redirection(redirections, variables); \
	printf("\nTest case (last redirect with args) %i: ", N); \
	compare_redirect_arguments(redirections, variables, out, in, LINE); \
    free (pipes); \
    free (spaces); \
    free (variables);

char			*preprocess(char *raw_input);
char			*preprocess_spaces(char *source);
char			*preprocess_pipes(char *source);
char            *preprocess_variables(char *source);
char			*preprocess_redirection(char *source);
int				is_escaped(char *char_ptr, char *start_str, char* escape_chars);
char			**preprocess_arguments(char **argv);
int 			expanded_string_length(char *source);
void			remove_substring(char *str, char *substr[2]);
void			find_end_redirection_string(char *redirections[3], char *source);
void			find_last_redirection(char *redirections[3], char *source);
void			rarg_substring(char *substring[2], char *start);
char			*rarg_end(char *redirection_position, char *source);
char			*rarg_start(char *redirection_position);
char			*redirection_argument_new(char *redirection);

#endif
