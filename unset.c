//
// Created by dinara on 8/6/21.
//

#include "basic_shell.h"

void unset(char **argv)
{
    char *value;
    int i;

    i = 1;
    while(argv && argv[i])
    {
        value = find_env_by_key(argv[i]);
        if(value)
        {
            remove_env(argv[i]);
            free(value);
        }
        i++;
    }
}