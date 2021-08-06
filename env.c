//
// Created by dinara on 8/6/21.
//
#include "basic_shell.h"
void env(void)
{
    char    **temp;
    int     i;

    i = 0;
    temp = get_status()->envp;
    while (temp[i])
    {
        ft_putstr_fd(temp[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return ;
}