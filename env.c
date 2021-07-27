//
// Created by savinykh-n on 25.07.2021.
//
#include "shell_status.h"
#include "libft.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>

char * find_env_by_key(char * str)
{
	char **envp;

	envp = get_status()->envp;
	char * result = 0;
	while (envp && !result) {
		char ** pair = ft_split(*envp, '=');
		if (ft_strncmp(pair[0], str, ft_strlen(str)) == 0) {
			result = ft_strdup(pair[1]);
			ft_split_free(pair);
		}
		envp++;
	}
	return result;
}

int get_int_from_env(char *key)
{
	char *tmp;
	int result;

	result = INT_MIN_MINISHELL;
	tmp = find_env_by_key(key);
	if (tmp)
	{
		result = ft_atoi(tmp);
		free(tmp);
	}
	return result;
}

size_t get_2d_array_size(char **array)
{
    size_t size;

    size = 0;
    while(*array!=0)
    {
        *array++;
        size++;
    }
    return (size);
}

int find_number_of_key(char *key)
{
    char    **env;
    int i;

    i = 0;
    env = get_status()->envp;
    while (env[i])
    {
        char ** pair = ft_split(env[i], '=');
        if (ft_strncmp(pair[0], key, ft_strlen(key)) == 0)
        {
            ft_split_free(pair);
            return (i);
        }
        ft_split_free(pair);
        i++;
    }
    return (-1);
}

void remove_env(char *key)
{
    char    **new_env;
    int     size;
    int     key_num;
    int     i;
    int     flag;

    new_env = 0;
    size = get_2d_array_size(get_status()->envp);
    new_env = malloc((size - 1) * sizeof(char*));
    key_num = find_number_of_key(key);
    i = 0;
    flag = 0;
    if (new_env && key_num >=0)
    {
        while(i < size - 1)
        {
            if(i == key_num)
                flag = 1;
            new_env[i + (i == key_num)] = ft_strdup(get_status()->envp[i+flag]);
            free(get_status()->envp[i]);
            i++;
        }
        new_env[size - 1] = 0;
        free(get_status()->envp);
        get_status()->envp = new_env;
    }
}

void update_env(char* key, char *value)
{
    int     key_num;
    int     update_len;
    char    *upd_str;
    char    **upd_env;
    int     size;
    int     i;

    key_num = find_number_of_key(key);
    upd_env = 0;
    i = 0;
    printf("%d\n", key_num);
    update_len = ft_strlen(key) + ft_strlen(value) + 2;
    if (key_num >= 0)
    {
        upd_str = (char *)malloc(update_len);
        ft_memcpy(upd_str, key, ft_strlen(key));
        upd_str[ft_strlen(key)] = '=';
        ft_memcpy(upd_str + ft_strlen(key) + 1, value, ft_strlen(value));
        upd_str[update_len - 1] = '\0';
        free(get_status()->envp[key_num]);
        get_status()->envp[key_num] = upd_str;
    }
    else
    {
        size = get_2d_array_size(get_status()->envp);
        upd_env = malloc((size + 2) * sizeof (char*));
        if(upd_env)
        {
            while (i < size)
            {
                upd_env[i] = ft_strdup(get_status()->envp[i]);
                free(get_status()->envp[i]);
                i++;
            }
            upd_str = (char *)malloc(update_len);
            ft_memcpy(upd_str, key, ft_strlen(key));
            upd_str[ft_strlen(key)] = '=';
            ft_memcpy(upd_str + ft_strlen(key) + 1, value, ft_strlen(value));
            upd_str[update_len - 1] = '\0';
            upd_env[i] = upd_str;
            upd_env[i+1] = 0;
            free(get_status()->envp);
            get_status()->envp = upd_env;
        }
    }
}

char **copy_env(char **orig_env)
{
    char    **res;
    int     size;
    int     i;

    res = 0;
    i = 0;
    size = get_2d_array_size(orig_env);
    res = malloc((size+1)*sizeof(char *));
    if(res)
    {
        while (i < size)
        {
            res[i] = ft_strdup(orig_env[i]);
            i++;
        }
        res[i] = 0;
    }
    return (res);
}

void print_env()
{
    char** env;
    int i;

    i = 0;
    env = get_status()->envp;
    while(env[i])
    {
        printf("%d) %s\n", i, env[i]);
        i++;
    }
}