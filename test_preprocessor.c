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

#define TEST_CASE_RESULT_1 "ls\02-lah\02atawana"
#define TEST_CASE_RESULT_2 "ls\02-lah\02atawana"
#define TEST_CASE_RESULT_3 "ls\02-lah\02atawanaatawana"
#define TEST_CASE_RESULT_4 "ls\02-lah\02atawana\02\'$USER\'"
#define TEST_CASE_RESULT_5 "ls\02-lah\02atawana\02\'$USER\'\02\'$USER\'\02\'$USER\'"
#define TEST_CASE_RESULT_6 "ls\02-lah\02atawana\02\'$USER\'\02\"atawana 123\"\02atawana"
#define TEST_CASE_RESULT_7 "ls\02-lah\02atawana\02\"atawana\""
#define TEST_CASE_RESULT_8 "ls\02-lah\02\'$USER\'"
#define TEST_CASE_RESULT_9 "ls\02/Users/atawana/../atawana"
#define TEST_CASE_RESULT_10 "ls\02atawana\02atawana\02$USERatawana"

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

void test_preprocessor()
{
    char *result;
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
	PREPROCESSOR_TEST_CASE(10, __LINE__)
}


