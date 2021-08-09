#ifndef MINISHELL_FILE_UTILS_H
#define MINISHELL_FILE_UTILS_H

int is_file_exist(char *filename);
char* is_bin_in_env(char *binary_name);
char *make_abs_path(char* path, char* filename);
char *make_bin_path(char * input);
int bin_check(char * path);
void create_empty_file(char *filename);

#endif //MINISHELL_FILE_UTILS_H
