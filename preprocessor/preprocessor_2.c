/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 03:25:30 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 13:23:16 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <redirection/redirection.h>
#include "preprocessor.h"
#include "libft.h"
#include "errors_printer/error_printer.h"
#include "shell_status/shell_status.h"

char	*preprocess_argument(char *argument)
{
	char	*result;
	char	*substr[2];
	char	*pos[2];

	result = ft_calloc(1, 2 + ft_strlen(argument));
	printf("LEAK %s:%i %p\n", __FILE__, __LINE__,  result);

	pos[W_POS] = result;
	pos[R_POS] = argument;
	substr[0] = ft_strpbrk(argument, "\"\'");
	if (!substr[0])
	{
		free(result);
		return (ft_strdup(argument));
	}
	while (substr[0] && *substr[0])
	{
		preprocess_argument_loop(pos, substr);
	}
	return (result);
}

char	**preprocess_arguments(char **argv)
{
	int		argc_count;
	char	**result;
	int		i;

	if (argv == 0)
		return (0);
	i = 0;
	argc_count = ft_split_count(argv);
	result = malloc((argc_count + 1) * sizeof(char *));
	printf("LEAK %s:%i %p\n", __FILE__, __LINE__,  result);
	while (argv[i])
	{
		result[i] = preprocess_argument(argv[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}

/*
 *
 * Return length of variable's name, length include '$' character
 * example:
 * $USER => 5
 */
int	variable_length(char *start_position)
{
	char	*last_position;

	last_position = ft_strpbrk2(start_position + 1, "\02\"$/ ><");
	return ((int)(last_position - start_position));
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
char	*variable_name(char *start_position, char *dollar_position)
{
	char	*result;
	int		length;

	if (is_escaped(dollar_position, start_position, "'"))
		return (0);
	length = variable_length(dollar_position);
	result = ft_calloc(length, 1);
	printf("LEAK %s:%i %p\n", __FILE__, __LINE__,  result);

	ft_slice_cpy(result, dollar_position + 1, dollar_position + length - 1);
	return (result);
}

/*
 * Return length of all variables length with '$' character in string, start
 * string position passed in start_position argument.
 * Escaped variables don't handle.
 * examples:
 * ls $USER -> 5
 * ls $USER$USER -> 10
 * ls $USER$USER '$USER' -> 10
 * ls '$USER' -> 0
 */
int	variables_length(char *start_position)
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
	return (result);
}
