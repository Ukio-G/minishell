#ifndef MINISHELL_FILE_UTILS_H
#define MINISHELL_FILE_UTILS_H
#include "command.h"

int	is_file_exist(char *filename);
char	*is_bin_in_env(char *binary_name);
char	*make_abs_path(char* path, char* filename);
char	*make_bin_path(char * input);
void	create_empty_file(char *filename);
int	is_builtin(char *cmd);
int exec_builtin(t_process_info *info);
t_executable_file_error	is_correct_executable(char *cmd);
int	is_directory(char *path);

#endif //MINISHELL_FILE_UTILS_H
