#ifndef MINISHELL_PERMISSION_H
#define MINISHELL_PERMISSION_H
#include <sys/stat.h>

typedef enum e_user_type
{
	PM_OWNER = 0, PM_GROUP = 1, PM_ALL = 2
} t_user_type;

typedef struct s_permission
{
	int execute;
	int write;
	int read;
	t_user_type target;
} t_permission;

t_permission get_permissions(char *path, t_user_type target);
t_permission current_user_permissions(char *path);
t_permission mode_to_permissions(mode_t mode, t_user_type type);
int is_file_owner(char *path);
int is_file_group_owner(char *path);
#endif
