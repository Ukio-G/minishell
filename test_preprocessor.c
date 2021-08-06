#include <stdio.h>
#include "preprocessor/preprocessor.h"
#include "libft.h"

void compare_string(char *a, char *b, int line)
{
    if (ft_strncmp(a, b, ft_strlen(a)) != 0)
    {
        printf("\033[0;31m");
        printf("\n|%s| not equal |%s| from line %i\n", a, b, line);
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

void test_preprocessor()
{
    char *result;
    result = preprocess("ls -lah $USER");
    compare_string(result, "ls\02-lah\02ukio", __LINE__);
    free(result);

    result = preprocess("ls -lah $USER");
    compare_string(result, "ls\02-lah\02ukio", __LINE__);
    free(result);

    result = preprocess("ls -lah $USER$USER");
    compare_string(result, "ls\02-lah\02ukioukio", __LINE__);
    free(result);

    result = preprocess("ls -lah $USER '$USER'");
    compare_string(result, "ls\02-lah\02ukio\02\'$USER\'", __LINE__);
    free(result);

    result = preprocess("ls -lah $USER '$USER' '$USER' '$USER'");
    compare_string(result, "ls\02-lah\02ukio\02\'$USER\'\02\'$USER\'\02\'$USER\'", __LINE__);
    free(result);

    result = preprocess("ls -lah $USER '$USER' \"$USER 123\" $USER");
    compare_string(result, "ls\02-lah\02ukio\02\'$USER\'\02\"ukio 123\"\02ukio", __LINE__);
    free(result);

    result = preprocess("ls -lah $USER \"$USER\"");
    compare_string(result, "ls\02-lah\02ukio\02\"ukio\"", __LINE__);
    free(result);

    result = preprocess("ls -lah '$USER'");
    compare_string(result, "ls\02-lah\02\'$USER\'", __LINE__);
    free(result);

    result = preprocess("ls $HOME/../$USER");
    compare_string(result, "ls\02-lah\02/home/ukio/../ukio", __LINE__);
    free(result);

//    result = preprocess("ls $USER $USER '$USER'$USER");
//    compare_string(result, "ls\02-lah\02ukio\02ukio\02$USERukio");
//    free(result);
}


