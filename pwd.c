//
// Created by dinara on 8/1/21.
//
#include "basic_shell.h"

void pwd()
{
    char *buffer_pwd;
    buffer_pwd = getcwd(NULL, 0);
    ft_putstr_fd(buffer_pwd, 1);
    ft_putstr_fd("\n", 1);
    if(buffer_pwd)
        free(buffer_pwd);
    return ;
}