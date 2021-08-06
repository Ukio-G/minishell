//
// Created by dinara on 7/27/21.
//

#include "basic_shell.h"

int process_path(char **argv, char** current_path)
{
    char *temp;
    int len;
    char *home = find_env_by_key("HOME");// надо проверить, нашлась ли такая переменная окружения
    if((ft_strncmp("~", argv[1], ft_strlen(argv[1])) == 0) || (ft_strncmp("~/", argv[1], ft_strlen(argv[1])) == 0))
    {
        *current_path = home;
        return (0);
    }
    if (argv[1][0] == '~' && argv[1][1] == '/') //надо делать подстановку домашнего каталога вместо ~
    {
        if(argv[1][ft_strlen(argv[1]) - 1] == '/')
            argv[1][ft_strlen(argv[1]) - 1] = '\0';
        len = (int)ft_strlen(home) + (int)ft_strlen(argv[1]);
        temp = malloc(len);
        ft_memcpy(temp, home, ft_strlen(home));
        ft_memcpy(temp + ft_strlen(home), argv[1] + 1, ft_strlen(argv[1] + 1));
        temp[len] = '\0';
        *current_path = temp;
        return(0);
    }
    free(home);
    if (argv[1][0] == '-' && ft_strlen(argv[1]) == 1)
    {
        char *oldpwd = find_env_by_key("OLDPWD");
        if(oldpwd == 0)
        {
           ft_putstr_fd("minishell: cd: OLDPWD not set", 1);
           free(oldpwd);
           return (-1);
        }
        *current_path = oldpwd;
        return(0);
    }
    *current_path = argv[1];
    return(0);
}

void cd(char **argv)
{
    char *current_path;
    char *old_path;
    char *info_msg;
    struct stat s;

    if(get_2d_array_size(argv) > 2 ) //у cd  может быть не более 1 аргумента
    {
        info_msg = "minishell: cd: too many arguments\n";
        ft_putstr_fd(info_msg, 1);
        return;
    }
    old_path = find_env_by_key("PWD");
    if (get_2d_array_size(argv) == 1) //значит cd без аргументов
    {
        current_path = find_env_by_key("HOME");
        chdir(current_path);
        update_env("PWD", current_path);
        update_env("OLDPWD", old_path);
        return;
    }
    // здесь нужно уже обработать ~ и -
    if (process_path(argv, &current_path) == -1)
    {
        if(old_path)
            free(old_path);
        return;
    }

    if(stat(current_path, &s) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 1);
        ft_putstr_fd(current_path, 1);
        ft_putstr_fd(": No such file or directory\n", 1);
        return;
    }
    mode_t mode = (s.st_mode >> (3 * 4)) << (3 * 4);
    if (mode != S_IFDIR)// если это не директория, то выдаем сообщение
    {
        ft_putstr_fd("minishell: cd: ", 1);
        ft_putstr_fd(current_path, 1);
        ft_putstr_fd(": Not a directory\n", 1);
        return;
    }
    chdir(current_path);
    update_env("PWD", current_path);
    update_env("OLDPWD", old_path);
    return;
}

