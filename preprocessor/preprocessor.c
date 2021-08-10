/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 12:31:21 by atawana           #+#    #+#             */
/*   Updated: 2021/08/09 17:10:20 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <redirection/redirection.h>
#include "preprocessor.h"
#include "libft.h"
#include "../errors_printer/error_printer.h"
#include "../shell_status.h"

void find_substr(char *substr[2], char *start_str, char *escape_chars)
{
	(substr)[0] = ft_strpbrk(start_str, escape_chars);
	if ((substr)[0])
	{
		(substr)[1] = ft_strchr((substr)[0] + 1, *(substr)[0]);
	}
}

void remove_substring(char *str, char *substr[2])
{
	char* end;
	int char_removed;
	int shift_count;

	if (!substr[0] || !substr[1] || !str)
		return;
	char_removed = (int)(substr[1] - substr[0] + 1);
	end = ft_strlen(str) + str;
	shift_count = (int)(end - substr[1]) - 1;
	ft_memmove(substr[0], substr[1] + 1, shift_count);
	ft_memset(end - (int)char_removed, 0, char_removed);
}

int is_escaped(char *char_ptr, char *start_str, char *escape_chars)
{
	char *substr[2];
	find_substr(substr, start_str, escape_chars);
	if (substr[0] && substr[1])
	{
		if (char_ptr < substr[0])
		{
			return 0;
		}
		else if (char_ptr > substr[1])
		{
			return is_escaped(char_ptr, substr[1] + 1, escape_chars);
		}
		else if (char_ptr == substr[0] || char_ptr == substr[1])
		{
			return 0;
		}
		else if (substr[0] < char_ptr && char_ptr < substr[1])
		{
			return 1;
		}
	}
	return 0;
}

char *preprocess_pipes(char *source)
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
		if (!is_escaped(pipe_position, result, "\"\'"))
		{
			*pipe_position = SPECIAL_PIPE;
		}
		pipe_position = ft_strchr(pipe_position + 1, '|');
	}
	return result;
}

char *preprocess_spaces(char *source)
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

char* preprocess_argument(char *argument)
{
	char *result;
	char *substr[2];
	char *pos[2];

	result = ft_calloc(1, 2 + ft_strlen(argument));
	pos[WRITE_POS] = result;
	pos[READ_POS] = argument;
	substr[0] = ft_strpbrk(argument, "\"\'");
	if (!substr[0])
	{
		free(result);
		return ft_strdup(argument);
	}
	while (substr[0] && *substr[0])
	{
		if (pos[READ_POS] < substr[0])
		{
			// Copy from read pos to open quote to write pos
			ft_slice_cpy(pos[WRITE_POS], pos[READ_POS], substr[0] - 1);
			// Move write pos
			pos[WRITE_POS] += (substr[0] - pos[READ_POS]);
		}
		// Find pair quote
		substr[1] = ft_strchr(substr[0] + 1, *substr[0]);

		// Copy quote content
		if ((substr[1] - substr[0]) > 1)
		{
			ft_slice_cpy(pos[WRITE_POS], substr[0] + 1, substr[1] - 1);
			pos[WRITE_POS] += (substr[1] - substr[0]) - 1;
		}
		// Find next opening quote or end of string
		substr[0] = ft_strpbrk2(substr[1] + 1, "\"\'");

		// Move read position
		pos[READ_POS] = substr[1] + 1;

		// Copy from last quote to end of string
		if (!*substr[0])
		{
			ft_slice_cpy(pos[WRITE_POS], pos[READ_POS], substr[0] - 1);
		}
	}

	return result;
}

char **preprocess_arguments(char **argv)
{
	int argc_count;
	char **result;
	int i;
	if (argv == 0)
		return 0;
	i = 0;
	argc_count = ft_split_count(argv);
	result = malloc((argc_count + 1) * sizeof(char *));
	while (argv[i])
	{
		result[i] = preprocess_argument(argv[i]);
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
	char *last_position;
	last_position = ft_strpbrk2(start_position + 1, "\02\"$/ ><");
	return (int) (last_position - start_position);
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
char *variable_name(char *start_position, char *dollar_position)
{
	char *result;
	int length;
	if (is_escaped(dollar_position, start_position, "'"))
		return 0;
	length = variable_length(dollar_position);
	result = ft_calloc(length, 1);
	ft_slice_cpy(result, dollar_position + 1, dollar_position + length - 1);
	return result;
}

/*
 * Return length of all variables length with '$' character in string, start string
 * position passed in start_position argument. Escaped variables don't handle.
 * examples:
 * ls $USER -> 5
 * ls $USER$USER -> 10
 * ls $USER$USER '$USER' -> 10
 * ls '$USER' -> 0
 */
int variables_length(char *start_position)
{
	int var_length;
	int result;
	char *dollar;
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

int expanded_variables_length(char *start_position)
{
	char *dollar_position;
	int result;
	int variable_len;
	char *v[2];
	DEBUG_PRINT_MACRO("start_position %s\n", start_position);
	dollar_position = ft_strchr(start_position, '$');
	result = 0;
	while (dollar_position)
	{
		if (!is_escaped(dollar_position, start_position, "'"))
		{
			v[VARIABLE_NAME] = variable_name(start_position, dollar_position);
			v[VARIABLE_VALUE] = find_env_by_key(v[VARIABLE_NAME]);
			variable_len = (int) ft_strlen(v[VARIABLE_NAME]);
			result += (int) ft_strlen(v[VARIABLE_VALUE]);
			free(v[VARIABLE_NAME]);
			free(v[VARIABLE_VALUE]);
		}
		else
		{
		    v[VARIABLE_NAME] = variable_name(start_position, dollar_position);
		    variable_len = (int) ft_strlen(v[VARIABLE_NAME]);
		    free(v[VARIABLE_NAME]);
		}
		dollar_position += (variable_len == 0);
		dollar_position = ft_strchr(dollar_position + variable_len, '$');
	}
	DEBUG_PRINT_MACRO("%s result %i\n", __func__, result);
	return result;
}

/*
 * Return size of new string, after expanding all variables, without null-terminated character
 * example:
 * $USER is "atawana"
 * source = "ls -lah $USER"
 * result: 15
 */
int expanded_string_length(char *source)
{
	int input_length;
	int vars_length;
	int expanded_vars_length;
	int no_vars_length;
	input_length = (int) ft_strlen(source);
	vars_length = variables_length(source);
	expanded_vars_length = expanded_variables_length(source);
	no_vars_length = input_length - vars_length;
	DEBUG_PRINT_MACRO("expanded_string_length = %i\n",
					  no_vars_length + expanded_vars_length);
	return no_vars_length + expanded_vars_length;
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
	pos[READ_POS] +=
			ft_strlen(v[VARIABLE_NAME]) + (pos[DOLLAR_POS] - pos[READ_POS]) + 1;

	// Free used resources
	free(v[VARIABLE_NAME]);
	free(v[VARIABLE_VALUE]);
}

char *preprocess_variables(char *source)
{
	char *result;
	char *pos[3];
	char *v[2];
	result = ft_calloc(1, (size_t) expanded_string_length(source) + 2);
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
					ft_memcpy(pos[WRITE_POS], pos[READ_POS],
							  pos[DOLLAR_POS] - pos[READ_POS]);
				continue;
			}

			// Update dollar pos
			pos[DOLLAR_POS] = ft_strchr2(pos[READ_POS], '$');

			// Copy to the end of source to result
			if (*pos[DOLLAR_POS] == 0)
				ft_memcpy(pos[WRITE_POS], pos[READ_POS],
						  pos[DOLLAR_POS] - pos[READ_POS]);
		}
	DEBUG_PRINT_MACRO("variables expanded |%s|\n", result);
	return result;
}

/*** Redirection block ***/

/*
 * Return pointer to first character after redirect and spaces.
 * Obtains pointer to first redirect character.
 * Example:
 * >> asdfg
 * |  |
 * |  rarg_start(redrection_position)
 * |
 * redrection_position
 */
char *rarg_start(char *redirection_position)
{
	char *start;

	start = redirection_position;
	start += (*start == start[1]);
	start++;
	start += (*start == '\02');
	if (*redirection_position == '>')
	{
		if (*start == '<')
			start = 0;
	}
	else if (*redirection_position == '<')
	{
		if (*start == '>')
			start = 0;
	}
	start += (*start == ' ');
	return start;
}

/*
 * Return pointer to last character redirect's argument
 * Obtains pointer to first redirect character.
 * Example:
 * cat <file.a <file.b >file.c >>file.d >"file<>.e"qwert
 * |                                    |              |
 * source                      redirection_position    |
 *                                                     |
 *                              rarg_end(redirection_position, source)
 */
char *rarg_end(char *redirection_position, char *source)
{
	char *start;
	char *end;

	start = rarg_start(redirection_position);
	if (!start)
		return 0;
	end = ft_strpbrk2(start, "\02><");
	while (*end && is_escaped(end, source, "\'\""))
	{
		end = ft_strpbrk2(start, "\02><");
	}
	end -= ft_isinset(*end, "\02><");
	while (*end == '\0')
		end--;
	return end;
}


/*
 * Set substring - pair pointer to start and end of redirection's argument
 * Obtains array of 2 char*, where will written result, and redirection position
 */
void rarg_substring(char *substring[2], char *start)
{
	substring[0] = rarg_start(start);
	substring[1] = rarg_end(start, start);
}

/*
 * Find last input and output redirections
 * redirections[LAST_OUT] - contains last out redirection (>> or >)
 * redirections[LAST_IN] - contains las input redirection (<< or <)
 * Will keep a pointer to the first character of redirection ( especially
 * relevant for cases >> <<)
 * Example:
 * cat <file.a <file.b >file.c >>file.d >file.e
 *             |                        |
 *       redirections[LAST_IN] |
 *                                      |
 *                      redirections[LAST_OUT]
 */
void find_last_redirection(char *redirections[3], char *source)
{
	char *redirection;

	redirection = ft_strpbrk2(source, "><");
	while (redirection && *redirection)
	{
		if (!is_escaped(redirection, source, "\'\""))
		{
			if (*redirection == '>')
				redirections[LAST_OUT] = redirection;
			else if (*redirection == '<')
				redirections[LAST_IN] = redirection;
			redirection += (redirection[1] == '>') + (redirection[1] == '<') + 1;
			redirection = ft_strpbrk2(redirection, "><");
		}
		else
		{
			redirection++;
		}
	}
}

/*
 * Find last redirection's argument character
 * Obtaining:
 * redirections - last input and output redirections
 * source - start of string
 * Save result to redirections[END_REDIRECTIONS_STRING]
 * redirections
 * Example:
 * cat <file.a <file.b >file.c >>file.d >file.e
 * |           |                        |     |
 * source      |                        |     |
 *             |                        |     |
 *       redirections[LAST_IN] |     |
 *                                      |     |
 *                      redirections[LAST_OUT]
 *                                            |
 *                    redirections[END_REDIRECTIONS_STRING]
 */
void find_end_redirection_string(char *redirections[3], char *source)
{
	char *end;

	if (redirections[LAST_IN] > redirections[LAST_OUT])
		end = redirections[LAST_IN];
	else
		end = redirections[LAST_OUT];
	redirections[END_REDIRECTIONS_STRING] = rarg_end(end, source);
}

char *redirection_argument_new(char *redirection)
{
	char *substring[2];
	char *result;

	rarg_substring(substring, redirection);
	if (!substring[0] || !substring[1])
		return 0;
	result = ft_calloc((substring[1] - substring[0]) + 2, 1);
	if (result)
		ft_slice_cpy(result, substring[0], substring[1]);
	return result;
}

void remove_redirections(char *redirections[3], char *source)
{
	char *substring[2];
	char *first;
	char *second;

	if (redirections[LAST_OUT] > redirections[LAST_IN])
	{
		first = redirections[LAST_OUT];
		second = redirections[LAST_IN];
	}
	else
	{
		first = redirections[LAST_IN];
		second = redirections[LAST_OUT];
	}
	if (first)
	{
		substring[0] = first;
		substring[1] = rarg_end(first, source);
		remove_substring(source, substring);
	}
	if (second)
	{
		substring[0] = second;
		substring[1] = rarg_end(second, source);
		remove_substring(source, substring);
	}
}

char *preprocess_redirection(char *source)
{
	char *result;
	char *trimmed;
	char *redirection[3];

	result = ft_strdup(source);
	ft_memset(redirection, 0, sizeof(void*) * 3);
	find_last_redirection(redirection, result);
	set_status_redirection(redirection);
	while (redirection[LAST_IN] || redirection[LAST_OUT])
	{
		// Create output file
		if (redirection[LAST_OUT])
			create_redirection_file(redirection[LAST_OUT]);
		// Remove last redirection
		remove_redirections(redirection, result);

		ft_memset(redirection, 0, sizeof(void*) * 3);
		find_last_redirection(redirection, result);
	}
	trimmed = ft_strtrim(result, "\02");
	free(result);
	return trimmed;
}

char *preprocess(char *raw_input)
{
	char *pipes;
	char *spaces;
	char *variables;
	char *redirection;

	init_redirection(&get_status()->redirect);
	pipes = preprocess_pipes(raw_input);
	spaces = preprocess_spaces(pipes);
	variables = preprocess_variables(spaces);
	redirection = preprocess_redirection(variables);

	DEBUG_PRINT_MACRO("Debug print pipes: |%s|\n", pipes);
	DEBUG_PRINT_MACRO("Debug print spaces: |%s|\n", spaces);
	DEBUG_PRINT_MACRO("Debug print variables: |%s|\n", variables);
	DEBUG_PRINT_MACRO("Debug print redirection: |%s|\n", redirection);
#ifdef PRINT_PREPROCESSED_INPUT
	printf("|%s|\n", redirection);
   #endif
	free(pipes);
	free(spaces);
	free(variables);
	return redirection;
}

