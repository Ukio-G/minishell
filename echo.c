//
// Created by dinara on 8/1/21.
//
#include "basic_shell.h"

void echo (char **argv)
{
    int n_flag;
    int i;
    int argv_len;

    n_flag = 0;
    i = 1;
    if (argv[i] == 0)
    {
        ft_putstr_fd("\n", 1);
        return;
    }
    if((ft_strncmp(argv[i], "-n", ft_strlen(argv[i]))) == 0)
    {
        n_flag = 1;
        argv = argv + 2;
    }
    argv_len = get_2d_array_size(argv);
    while(i < argv_len)
    {
        if(n_flag)
        {
            while ((ft_strncmp(argv[i], "-n", ft_strlen(argv[i]))) == 0)
                i++;
        }
        ft_putstr_fd(argv[i], 1);
        if (i != argv_len - 2)
            ft_putchar_fd(' ', 1);
        i++;
    }
    if(!n_flag)
        ft_putchar_fd('\n', 1);
}