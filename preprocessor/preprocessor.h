/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:47:38 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 10:49:27 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPROCESSOR_H
# define PREPROCESSOR_H

/*
 * Replacement for not escaped pipes
 */
# define SPECIAL_PIPE 0x01

/*
 * Command and arguments delimiter replacement. Spaces/tabs -> 0x02
 */
# define SPECIAL_ARGS_DELIMITER 0x02

/*
 *  Env variable Key
 */
# define V_NAME 0

/*
 * Env variable value
 */
# define V_VAL 1

/*
 * Read position
 */
# define R_POS 0

/*
 * Write position
 */
# define W_POS 1

/*
 * Dollar position
 */
# define D_POS 2

/*
 * Index of last output redirection in arrays
 */
# define LAST_OUT 0

/*
 * Index of last input redirection in arrays
 */
# define LAST_IN 1
# define END_REDIRECTIONS_STRING 2

char	*preprocess(char *raw_input);
char	*preprocess_spaces(char *source);
char	*preprocess_pipes(char *source);
char	*preprocess_variables(char *source);
char	*preprocess_redirection(char *source);
int		is_escaped(char *char_ptr, char *start_str, char *escape_chars);
char	**preprocess_arguments(char **argv);
int		expanded_string_length(char *source);
void	remove_substring(char *str, char *substr[2]);
void	find_end_redirection_string(char *redirections[3], char *source);
void	find_last_redirection(char *redirections[3], char *source);
void	rarg_substring(char *substring[2], char *start);
char	*rarg_end(char *redirection_position, char *source);
char	*rarg_start(char *redirection_position);
char	*redirection_argument_new(char *redirection);
char	*preprocess_argument(char *argument);
char	*variable_name(char *start_position, char *dollar_position);
int		variables_length(char *start_position);
void	preprocess_variables_loop(char *pos[3], char *v[2], char *source);
void	expand_variable(char **source, char *pos[3], char *v[2]);
int		expanded_variables_length_loop(char *dollar_position,
			char *start_position, char *v[2], int *result);
void	preprocess_argument_loop(char *pos[2], char *substr[2]);
#endif
