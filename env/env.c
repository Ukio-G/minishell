//
// Created by savinykh-n on 25.07.2021.
//
#include "../shell_status.h"
#include "libft.h"

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

	result = INT32_MIN;
	tmp = find_env_by_key(key);
	if (tmp)
	{
		result = ft_atoi(tmp);
		free(tmp);
	}
	return result;
}
