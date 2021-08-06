//
// Created by dinara on 8/6/21.
//

#include "basic_shell.h"

void swap_string_in_array(char **s1, char **s2)
{
    char *temp;

    temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

void sort_and_print()
{
    char **temp;
    int i;
    int j;
    int size;
    int len;

    temp = get_status()->envp;
    size = get_2d_array_size(temp);
    i = 0;
    while(i < size - 1)
    {
        j = size - 1;
        while (j > i)
        {
            len = ft_strlen(temp[j]);
            if (len < ft_strlen(temp[j - 1]))
                len = ft_strlen(temp[j - 1]);
            if (ft_strncmp(temp[j - 1], temp[j], len) > 0)
                swap_string_in_array(&temp[j - 1], &temp[j]);
            j--;
        }
        i++;
    }
    i = 0;
    while (temp[i])
    {
        ft_putstr_fd(temp[i], 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
    return ;
}

void export (char **argv)
{
    if(get_2d_array_size(argv) == 1)// export указан без аргументов, значит только отсортировать и вывести
    {
        sort_and_print();
        return;
    }

    return ;
}
