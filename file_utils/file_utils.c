#include "permission.h"
#include "../shell_status.h"
#include <sys/stat.h>

int is_file_exist(char *abs_filename)
{
	struct stat s;
	return (stat(abs_filename, &s) == 0);
}

t_permission mode_to_permissions(mode_t mode, t_user_type type)
{
	t_permission result;
	result.execute = (mode & (01 << (int)type * 3));
	result.write = (mode & (02 << (int)type * 3));
	result.read = (mode & (04 << (int)type * 3));
	return result;
}

int is_file_owner(char *path)
{
	struct stat s;
	if (stat(path, &s) == 0)
	{
		return (int)s.st_uid == get_status()->uid;
	}
	return 0;
}

int is_file_group_owner(char *path)
{
	struct stat s;
	if (stat(path, &s) == 0)
	{
		return (int)s.st_gid == get_status()->gid;
	}
	return 0;
}

t_permission current_user_permissions(char *path)
{
	struct stat s;

	if (stat(path, &s) == 0)
	{
		if (is_file_owner(path))
		{
			return mode_to_permissions(s.st_mode, PM_OWNER);
		}
		else if (is_file_group_owner(path))
		{
			return mode_to_permissions(s.st_mode, PM_GROUP);
		}
		else
		{
			return mode_to_permissions(s.st_mode, PM_ALL);
		}
	}
	t_permission failsafe = {0, 0, 0, 0};
	return failsafe;
}

t_permission get_permissions(char *path, t_user_type target)
{
	struct stat s;

	if (stat(path, &s) == 0)
	{
		return mode_to_permissions(s.st_mode, target);
	}
	t_permission failsafe = {0, 0, 0, 0};
	return failsafe;
}