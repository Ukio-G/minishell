#ifndef EXECUTABLE_FILE_ERROR_H
#define EXECUTABLE_FILE_ERROR_H

typedef enum e_executable_file
{
	E_FILE_NO_ERROR,
	E_FILE_NO_PERMISSION, // bash: ./input.c: Permission denied 126
	E_FILE_IS_DIRECTORY,  // bash: ./documents: is a directory 126
	E_FILE_CMD_NOT_FOUND, // bash: documents: command not found 127
	E_FILE_FILE_NOT_FOUND // bash: ./sadaf: No such file or directory 127
} t_executable_file_error;

#endif //EXECUTABLE_FILE_ERROR_H