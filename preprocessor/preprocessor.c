#include "preprocessor.h"
#include "libft.h"
#include "../errors_printer/error_printer.h"

int is_escaped(char *char_ptr, char *start_str, char* escape_chars)
{
	char *substr[2];

	substr[0] = ft_strpbrk(start_str, escape_chars);
	if (substr[0])
	{
		substr[1] = ft_strchr(substr[0] + 1, *substr[0]);
		if (!substr[1])
		{
			// TODO: parser error - stop minishell
			exit(100);
		}
	}
	if (substr[0] && substr[1])
	{
		if (char_ptr < substr[0])
		{
			return 0;
		}
		else if (char_ptr > substr[1])
		{
			return is_escaped(char_ptr, substr[1], escape_chars);
		}
		else if (char_ptr == substr[0] || char_ptr == substr[1])
		{
			// TODO: parser error - stop minishell
			exit(100);
		}
		else if (substr[0] > char_ptr && char_ptr < substr[1])
		{
			return 1;
		}
	}
	return 0;
}

char* preprocess_pipes(char *source)
{
	char *pipe_position;
	char *result;

	result = ft_strdup(source);
	if (!result)
	{
		exit(MINISHELL_MEMORY_ERROR);
	}
	pipe_position = ft_strchr(result, '|');
	while (pipe_position)
	{
		if (!is_escaped(pipe_position, result, "\"'"))
		{
			*pipe_position = SPECIAL_PIPE;
		}
		pipe_position = ft_strchr(pipe_position + 1, '|');
	}

	return result;
}

char* preprocess_spaces(char *source)
{
	char *space_position;
	char *result;

	result = ft_strdup(source);
	if (!result)
	{
		exit(MINISHELL_MEMORY_ERROR);
	}
	space_position = ft_strchr(result, ' ');
	while (space_position)
	{
		if (!is_escaped(space_position, result, "\"'"))
		{
			*space_position = SPECIAL_ARGS_DELIMITER;
		}
		space_position = ft_strchr(space_position + 1, ' ');
	}

	return result;
}

char* preprocess_variables(char *source)
{

}

char *preprocess(char *raw_input)
{
	char *pipes;
	char *spaces;
	char *variables;

	pipes = preprocess_pipes(raw_input);
	spaces = preprocess_spaces(pipes);
//	variables = preprocess_variables(spaces);

	free(pipes);
//	free(spaces);
//	free(variables);
//	return variables;

	return spaces;
}

