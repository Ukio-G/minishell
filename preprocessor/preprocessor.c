#include <stdio.h>
#include "preprocessor.h"
#include "libft.h"
#include "../errors_printer/error_printer.h"
#include "../shell_status.h"

void find_substr(char* substr[2], char *start_str, char* escape_chars)
{
	(substr)[0] = ft_strpbrk(start_str, escape_chars);
	if ((substr)[0])
	{ 
		(substr)[1] = ft_strchr((substr)[0] + 1, *(substr)[0]);
	}
}

int is_escaped(char *char_ptr, char *start_str, char* escape_chars)
{
	char	*substr[2];
	find_substr(substr, start_str, escape_chars);

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
		else if (substr[0] < char_ptr && char_ptr < substr[1])
		{
			return 1;
		}
	}
	return 0;
}

char* preprocess_pipes(char *source)
{
	char	*pipe_position;
	char	*result;

	result = ft_strdup(source);
	if (!result)
	{
		exit(MINISHELL_MEMORY_ERROR);
	}
	pipe_position = ft_strchr(result, '|');
	while (pipe_position)
	{
		if (!is_escaped(pipe_position, result, "\"\'"))
		{
			*pipe_position = SPECIAL_PIPE;
		}
		pipe_position = ft_strchr(pipe_position + 1, '|');
	}

	return result;
}

char* preprocess_spaces(char *source)
{
	char	*space_position;
	char	*result;

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

char **preprocess_arguments(char **argv)
{
	int		argc_count;
	char	**result;
	int		i;

	i = 0;
	argc_count = ft_split_count(argv);
	result = malloc((argc_count + 1) * sizeof(char*));
	while (argv[i])
	{
		result[i] = ft_strtrim(argv[i], "\'\"");
		i++;
	}
	result[i] = 0;
	return result;
}

/*
 *
 * Return length of variable's name, length include '$' character
 * example:
 * $USER => 5
 */
int variable_length(char *start_position)
{
	char	*last_position;

	last_position = ft_strpbrk2(start_position + 1, "\02\"$");
	return (int)(last_position - start_position);
}

/*
 * Return new allocated memory, with only variable name (without $ character)
 * Obtains 2 arguments - start string position and dollar position
 * If variable escaped - return 0
 * example:
 *
 * la -lah $USER
 * |       |
 * | dollar_position
 * |
 * start_position
 *
 * return string "USER" in new allocated memory
 */
char* variable_name(char *start_position, char *dollar_position)
{
    char	*result;
    int		length;

    if (is_escaped(dollar_position, start_position, "'"))
        return 0;
    length = variable_length(dollar_position);
    result = ft_calloc(length, 1);
    ft_slice_cpy(result, dollar_position + 1, dollar_position + length - 1);
    return result;
}

int variables_length(char *start_position)
{
	int		var_length;
	int		result;
	char	*dollar;

	result = 0;
	dollar = ft_strchr(start_position, '$');
	while (dollar)
	{
		if (!is_escaped(dollar, start_position, "'"))
		{
			if (dollar[1] == '$')
				var_length = 2;
			else
				var_length = variable_length(dollar);
			result += var_length;
			dollar += var_length;
		}
		else
			dollar++;
		dollar = ft_strchr(dollar, '$');
	}
	return result;
}

int			expanded_variables_length(char *start_position)
{
	char	*substring[2];
	char	*tmp[2];
	size_t	len;
	int		result;

	printf("start_position %s",start_position);

	substring[0] = ft_strchr(start_position, '$');
	result = 0;
	while (substring[0])
	{
		substring[1] = ft_strpbrk2(substring[0], "\02\"$");
		if (!is_escaped(substring[0], start_position, "'"))
		{
			len = substring[1] - substring[0] - 1;
			tmp[0] = ft_strndup(substring[0] + 1, len);
			tmp[1] = find_env_by_key(tmp[0]);
			result += (int) ft_strlen(tmp[1]);
#ifdef DEBUG_PRINT
			printf("tmp[0] = %s tmp[1] = %s, len = %i\n", tmp[0], tmp[1], len);
#endif
			free(tmp[0]);
			free(tmp[1]);
		}
		substring[0] = ft_strchr(substring[1], '$');
#ifdef DEBUG_PRINT
		printf("substring[0] = %s substring[1] = %s\n", substring[0], (*substring[1]) ? (substring[1]) : 0);
#endif

	}
	return result;
}

int expanded_string_length(char *source)
{
	int		input_length;
	int		vars_length;
	int		expanded_vars_length;
	int		no_vars_length;

	input_length = (int)ft_strlen(source);
	vars_length = variables_length(source);
	expanded_vars_length = expanded_variables_length(source);
	no_vars_length = input_length - vars_length;

	printf("expanded_string_length = %i\n", no_vars_length + expanded_vars_length);

	return no_vars_length + expanded_vars_length + 1;
}

void expand_variable(char **source, char *pos[3], char *v[2])
{
    // Copy before dollar
    ft_memcpy(pos[WRITE_POS], pos[READ_POS], pos[DOLLAR_POS] - pos[READ_POS]);

    // Move write position
    pos[WRITE_POS] += (pos[DOLLAR_POS] - pos[READ_POS]);

    // Determinate pair key => value
    v[VARIABLE_NAME] = variable_name(*source, pos[DOLLAR_POS]);
    v[VARIABLE_VALUE] = find_env_by_key(v[VARIABLE_NAME]);

    // Copy variable value
    ft_memcpy(pos[WRITE_POS], v[VARIABLE_VALUE], ft_strlen(v[VARIABLE_VALUE]));

    // Move read and write position
    pos[WRITE_POS] += ft_strlen(v[VARIABLE_VALUE]);
    pos[READ_POS] += ft_strlen(v[VARIABLE_NAME]) + (pos[DOLLAR_POS] - pos[READ_POS]) + 1;

    // Free used resources
    free(v[VARIABLE_NAME]);
    free(v[VARIABLE_VALUE]);
}


char* preprocess_variables(char *source)
{
	char	*result;
	char	*pos[3];
	char	*v[2];

	result = ft_calloc(1, (size_t)expanded_string_length(source));
	pos[WRITE_POS] = result;
	pos[READ_POS] = source;
	pos[DOLLAR_POS] = ft_strchr2(source, '$');

	// No one variable
	if (*pos[DOLLAR_POS] == 0)
		ft_memcpy(result, source, ft_strlen(source));
	else
		while (*pos[DOLLAR_POS])
		{
		    if (!is_escaped(pos[DOLLAR_POS], source, "\'"))
		        expand_variable(&source, pos, v);
		    else
		    {
		        pos[DOLLAR_POS] = ft_strchr2(pos[DOLLAR_POS] + 1, '$');
		        if (*pos[DOLLAR_POS] == 0)
		            ft_memcpy(pos[WRITE_POS], pos[READ_POS], pos[DOLLAR_POS] - pos[READ_POS]);
                continue;
		    }

			// Update dollar pos
			pos[DOLLAR_POS] = ft_strchr2(pos[READ_POS], '$');

			// Copy to the end of source to result
			if (*pos[DOLLAR_POS] == 0)
				ft_memcpy(pos[WRITE_POS], pos[READ_POS], pos[DOLLAR_POS] - pos[READ_POS]);
		}
	printf("variables expanded |%s|\n", result);
	return result;
}

char *preprocess(char *raw_input)
{
	char	*pipes;
	char	*spaces;
	char	*variables;

	pipes = preprocess_pipes(raw_input);
	spaces = preprocess_spaces(pipes);
	variables = preprocess_variables(spaces);

	free(pipes);
	free(spaces);
	return variables;
}

