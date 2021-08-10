#include <printf.h>
#include "libft.h"
#include "pipes.h"
#include "../ft_vector/ft_vector.h"
#include "../shell_status.h"

t_ft_vector create_pipes_set(t_ft_vector commands)
{
	t_ft_vector result;
	int tmp[2];
	int i;

	i = 0;
	ft_vector_init(&result, sizeof(int));
	while (i < (int)commands.size - 1)
	{
		pipe(tmp);
		ft_vector_add(&result, tmp + 1);
		ft_vector_add(&result, tmp);
		i++;
	}
	return result;
}

void close_all_pipes()
{
	t_ft_vector pset = get_status()->pipes_set;
	while (ft_vector_iter(&pset))
	{
		int *fd;
		fd = ft_vector_iter_value(&pset);
		close(*fd);
	}
}

void bind_process_with_pipes(t_ft_vector processes, t_ft_vector pipes)
{
	t_process_info *info[2];
	int i = 0;
	int j = 0;

	while ((int)processes.size - 1 > i)
	{
#ifdef DEBUG_PRINT
		printf("pipes bind %d %d\n",*(int*)at(&pipes, j), *(int*)at(&pipes, j + 1));
#endif
		info[0] = at(&processes, i);
		info[1] = at(&processes, i + 1);
		info[0]->out_d = *(int*)at(&pipes, j);
		info[1]->in_d = *(int*)at(&pipes, j + 1);
		j += 2;
		i++;
	}
}