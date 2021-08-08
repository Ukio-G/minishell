#include "shell_status.h"
#include "libft.h"
#include "env_utils.h"
#include <stdlib.h>

void	force_remove_env(char *key)
{
	char    **new_env;
	int     size;
	int     key_num;
	int     i;
	int     flag;

	size = get_2d_array_size(get_status()->envp);
	new_env = malloc(size * sizeof(char *));
	key_num = find_number_of_key(key);
	i = 0;
	flag = 0;
	if (new_env && key_num >=0)
	{
		while(i < size - 1)
		{
			if(i == key_num)
				flag = 1;
			new_env[i] = ft_strdup(get_status()->envp[i + flag]);
			free(get_status()->envp[i]);
			i++;
		}
		new_env[size - 1] = 0;
		free(get_status()->envp);
		get_status()->envp = new_env;
	}
	return ;
}
