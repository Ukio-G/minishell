#ifndef MINISHELL_ERROR_PRINTER_H
#define MINISHELL_ERROR_PRINTER_H

#include "file_utils.h"

#define MINISHELL_MEMORY_ERROR 250

void print_error(t_executable_file_error file, char *path);
int code_from_error(t_executable_file_error file);
void print_pipe_error();
void print_dot_error();

#endif
