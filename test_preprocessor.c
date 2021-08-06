#include <stdio.h>
#include "preprocessor/preprocessor.h"
#include "libft.h"

void compare_string(char *a, char *b)
{
    if (ft_strncmp(a, b, ft_strlen(a)) != 0)
    {
        printf("%s not equal %s\n", a, b);
        exit(1);
    }
}

void test_preprocessor()
{
//    char *result;
//    result = preprocess("ls -lah $USER");
//    compare_string(result, "ls\02-lah\02ukio");
//    free(result);
//
//    result = preprocess("ls -lah $USER");
//    compare_string(result, "ls\02-lah\02ukio");
//    free(result);
//
//    result = preprocess("ls -lah $USER$USER");
//    compare_string(result, "ls\02-lah\02ukioukio");
//    free(result);
//
//    result = preprocess("ls -lah $USER '$USER'");
//    compare_string(result, "ls\02-lah\02ukio\02$USER");
//    free(result);
//
//    result = preprocess("ls -lah $USER '$USER' '$USER' '$USER'");
//    compare_string(result, "ls\02-lah\02ukio\02$USER\02$USER\02$USER");
//    free(result);

//    result = preprocess("ls -lah $USER '$USER' "$USER 123" $USER");
//    compare_string(result, "ls\02-lah\02ukio\02$USER\02ukio 123\02ukio");
//    free(result);

//    result = preprocess("ls -lah $USER \"$USER\"");
//    compare_string(result, "ls\02-lah\02ukio\02ukio");
//    free(result);
//
//    result = preprocess("ls -lah '$USER'");
//    compare_string(result, "ls\02-lah\02$USER");
//    free(result);
//
//    result = preprocess("ls $HOME/../$USER");
//    compare_string(result, "ls\02-lah\02/home/ukio/../ukio");
//    free(result);

//    result = preprocess("ls $USER $USER '$USER'$USER");
//    compare_string(result, "ls\02-lah\02ukio\02ukio\02$USERukio");
//    free(result);
}


