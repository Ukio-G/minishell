/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 02:47:38 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 02:47:38 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PREPROCESSOR_H
# define MINISHELL_PREPROCESSOR_H

# define SPECIAL_PIPE 0x01
# define SPECIAL_ARGS_DELIMITER 0x02
# define VARIABLE_NAME 0
# define VARIABLE_VALUE 1
# define READ_POS 0
# define WRITE_POS 1
# define DOLLAR_POS 2
# define LAST_OUT 0
# define LAST_IN 1
# define END_REDIRECTIONS_STRING 2


char	*preprocess(char *raw_input);
char	*preprocess_spaces(char *source);
char	*preprocess_pipes(char *source);
char	*preprocess_variables(char *source);
char	*preprocess_redirection(char *source);
int		is_escaped(char *char_ptr, char *start_str, char* escape_chars);
char	**preprocess_arguments(char **argv);
int 	expanded_string_length(char *source);
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

#endif
