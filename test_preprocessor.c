#include <stdio.h>
#include "preprocessor/preprocessor.h"
#include "libft.h"

#define TEST_CASE_1 "ls -lah $USER"
#define TEST_CASE_2 "ls -lah $USER"
#define TEST_CASE_3 "ls -lah $USER$USER"
#define TEST_CASE_4 "ls -lah $USER '$USER'"
#define TEST_CASE_5 "ls -lah $USER '$USER' '$USER' '$USER'"
#define TEST_CASE_6 "ls -lah $USER '$USER' \"$USER 123\" $USER"
#define TEST_CASE_7 "ls -lah $USER \"$USER\""
#define TEST_CASE_8 "ls -lah '$USER'"
#define TEST_CASE_9 "ls $HOME/../$USER"
#define TEST_CASE_10 "ls $USER $USER '$USER'$USER"

#define TEST_CASE_RESULT_1 "ls\02-lah\02" USER_MACRO ""
#define TEST_CASE_RESULT_2 "ls\02-lah\02" USER_MACRO ""
#define TEST_CASE_RESULT_3 "ls\02-lah\02" USER_MACRO "" USER_MACRO ""
#define TEST_CASE_RESULT_4 "ls\02-lah\02" USER_MACRO "\02\'$USER\'"
#define TEST_CASE_RESULT_5 "ls\02-lah\02" USER_MACRO "\02\'$USER\'\02\'$USER\'\02\'$USER\'"
#define TEST_CASE_RESULT_6 "ls\02-lah\02" USER_MACRO "\02\'$USER\'\02\"" USER_MACRO " 123\"\02" USER_MACRO ""
#define TEST_CASE_RESULT_7 "ls\02-lah\02" USER_MACRO "\02\"" USER_MACRO "\""
#define TEST_CASE_RESULT_8 "ls\02-lah\02\'$USER\'"
#define TEST_CASE_RESULT_9 "ls\02" HOME_MACRO "" USER_MACRO "/../" USER_MACRO ""
#define TEST_CASE_RESULT_10 "ls\02" USER_MACRO "\02" USER_MACRO "\02$USER" USER_MACRO ""


void print_binary_string(char * str)
{
	while (*str)
	{
		printf("|%02x|", *str);
		str++;
	}
	printf("\n");
}

void compare_string(char *a, char *b, int line)
{
    if (ft_strncmp(a, b, ft_strlen(a)) != 0)
    {
        printf("\033[0;31m");
        printf("\n|%s| not equal |%s| from line %i\n", a, b, line);
		print_binary_string(a);
		print_binary_string(b);
        printf("\033[0m");
        exit(1);
    }
    else
    {
        printf("\033[0;32m");
        printf("\n|%s| equal |%s|\n", a, b);
        printf("\033[0m");
    }
}

void compare_length(int a, int b, int line, char *s)
{
	if (a != b)
	{
		printf("\033[0;31m");
		printf("|%s| incorrect length on line %i. Calculated: %i; real: %i\n", s, line, a, b);
		print_binary_string(s);
		printf("\033[0m");
		exit(1);
	}
	else
	{
		printf("\033[0;32m");
		printf("|%s| correct length: %i\n", s, a);
		printf("\033[0m");
	}
}

void compare_removed_string(char *str1, char *str2, int line)
{
	if (ft_strncmp(str1, str2, ft_strlen(str2) + 1) == 0)
	{
		printf("\033[0;32m");
		printf("|%s| string removed correctly\n", str1);
		printf("\033[0m");
	}
	else
	{
		printf("\033[0;31m");
		printf("On line %i\n", line);
		printf("string removed incorrected. \nPreprocessed: |%s|\nExpected: |%s|\n", str1, str2);
		print_binary_string(str1);
		print_binary_string(str2);
		printf("\033[0m");
		exit(1);
	}
}

void compare_last_find_redirection(char *redirections[3], char *source, int out_idx_expected, int in_idx_expected, int line)
{
	int out_idx;
	int in_idx;

	out_idx = (redirections[LAST_OUT_REDIRECT]) ? (int)(redirections[LAST_OUT_REDIRECT] - source) : -1;
	in_idx = (redirections[LAST_IN_REDIRECT]) ? (int)(redirections[LAST_IN_REDIRECT] - source) : -1;

	if ((out_idx == out_idx_expected) && (in_idx == in_idx_expected))
	{
		printf("\033[0;32m");
		printf("Ok! Out idx: %i; In idx: %i\n", out_idx, in_idx);
		printf("\033[0m");
	}
	else
	{
		printf("\033[0;31m");
		printf("Something wrong! Out: %i (expected: %i); In %i (expected %i)\n", out_idx, out_idx_expected, in_idx, in_idx_expected);
		printf("String: %s\n", source);
		print_binary_string(source);
		printf("\033[0m");
		exit(1);
	}
}


void compare_redirect_arguments(char *redirections[3], char *source, char *out_expected, char *in_expected, int line)
{
	char out_buf[512];
	char in_buf[512];
	char *out_arg[2];
	char *in_arg[2];

	ft_memset(out_buf, 0, 512);
	ft_memset(in_buf, 0, 512);

	if (redirections[LAST_OUT_REDIRECT] && out_expected)
	{
	    out_arg[0] = rarg_start(redirections[LAST_OUT_REDIRECT]);
		out_arg[1] = rarg_end(redirections[LAST_OUT_REDIRECT], source);
		ft_slice_cpy(out_buf,out_arg[0], out_arg[1]);
        printf("stdout compare:\n");
		compare_string(out_buf, out_expected, line);
	}

	if (redirections[LAST_IN_REDIRECT] && in_expected)
	{
	    in_arg[0] = rarg_start(redirections[LAST_IN_REDIRECT]);
	    in_arg[1] = rarg_end(redirections[LAST_IN_REDIRECT], source);
	    ft_slice_cpy(in_buf,in_arg[0], in_arg[1]);
	    printf("stdin compare:\n");
	    compare_string(in_buf, in_expected, line);
	}
}

void test_preprocessor_length_detector()
{
	char	*pipes;
	char	*spaces;
	int		length;

	PREPROCESSOR_LENGTH_TEST_CASE(1, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(2, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(3, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(4, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(5, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(6, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(7, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(8, __LINE__)
	PREPROCESSOR_LENGTH_TEST_CASE(9, __LINE__)
	// PREPROCESSOR_LENGTH_TEST_CASE(10, __LINE__)
}

void test_remove_string()
{
	char *expected;
	char *preprocessed;
	char *substring[2];

	REMOVE_STRING_TEST_CASE(1, __LINE__)
	REMOVE_STRING_TEST_CASE(2, __LINE__)
	REMOVE_STRING_TEST_CASE(3, __LINE__)
	REMOVE_STRING_TEST_CASE(4, __LINE__)
	REMOVE_STRING_TEST_CASE(5, __LINE__)
	REMOVE_STRING_TEST_CASE(6, __LINE__)
}


void test_find_redirection()
{
	char *redirections[3];
	char *source;

	char *pipes;
	char *spaces;
	char *variables;

	TEST_FIND_LAST_REDIRECTION_CASE(1, __LINE__)
	TEST_FIND_LAST_REDIRECTION_CASE(2, __LINE__)
	TEST_FIND_LAST_REDIRECTION_CASE(3, __LINE__)
	TEST_FIND_LAST_REDIRECTION_CASE(4, __LINE__)
	TEST_FIND_LAST_REDIRECTION_CASE(5, __LINE__)
	TEST_FIND_LAST_REDIRECTION_CASE(6, __LINE__)
	TEST_FIND_LAST_REDIRECTION_CASE(7, __LINE__)
}

void test_last_redirections_args()
{
    char *redirections[3];
    char *source;

    char *pipes;
    char *spaces;
    char *variables;

    char *out;
    char *in;

    TEST_LAST_REDIRECTIONS_ARGUMENT(1, __LINE__)
    TEST_LAST_REDIRECTIONS_ARGUMENT(2, __LINE__)
    TEST_LAST_REDIRECTIONS_ARGUMENT(3, __LINE__)
    TEST_LAST_REDIRECTIONS_ARGUMENT(4, __LINE__)
    TEST_LAST_REDIRECTIONS_ARGUMENT(5, __LINE__)
    TEST_LAST_REDIRECTIONS_ARGUMENT(6, __LINE__)
    TEST_LAST_REDIRECTIONS_ARGUMENT(7, __LINE__)
}


void test_preprocessor()
{
    char *result;

	test_find_redirection();
	test_last_redirections_args();
	test_remove_string();
	test_preprocessor_length_detector();
	PREPROCESSOR_TEST_CASE(1, __LINE__)
	PREPROCESSOR_TEST_CASE(2, __LINE__)
	PREPROCESSOR_TEST_CASE(3, __LINE__)
	PREPROCESSOR_TEST_CASE(4, __LINE__)
	PREPROCESSOR_TEST_CASE(5, __LINE__)
	PREPROCESSOR_TEST_CASE(6, __LINE__)
	PREPROCESSOR_TEST_CASE(7, __LINE__)
	PREPROCESSOR_TEST_CASE(8, __LINE__)
	PREPROCESSOR_TEST_CASE(9, __LINE__)
//	PREPROCESSOR_TEST_CASE(10, __LINE__)
}


