/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweeper <lweeper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 20:29:14 by lweeper           #+#    #+#             */
/*   Updated: 2021/08/08 20:32:03 by lweeper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# define INT_MIN_MINISHELL -2147483646
# define INVISIBLE_PREFIX '\03'
# include "shell_status.h"
# include "libft.h"
# include <stdlib.h>

size_t	get_2d_array_size(char **array);
char	*find_env_by_key(char *str);
int		get_int_from_env(char *key);
char	*find_env_by_invisible_key(char *str);
char	**copy_env(char **orig_env);
void	update_env(char *key, char *value);
void	remove_env(char *key);
int		find_number_of_key(char *key);
int		is_valid_identifier(char *id);
void	print_error_msg(char *op, char *bad_id, char *msg);

#endif
