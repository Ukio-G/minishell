/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 23:53:52 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:19:20 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include "libft.h"

# define LOG_ERRORS 1

typedef enum e_ft_vector_errors
{
	NO_ERROR,
	MALLOC_ERROR,
	OUT_OF_RANGE,
	INVALID_ITERATOR
}	t_ft_vector_errors;

typedef struct s_ft_vector
{
	void				*data;
	size_t				element_size;
	size_t				allocated;
	size_t				size;
	void				*iterator;
	size_t				iterator_idx;
	t_ft_vector_errors	error;
}						t_ft_vector;

void				ft_vector_reallocate(t_ft_vector *vector);
void				ft_vector_add(t_ft_vector *vector, void *data);
void				ft_vector_init(t_ft_vector *vector, size_t elem_size);
void				*at(t_ft_vector *vector, size_t i);
void				print_vector_error(const char *str);
void				*ft_vector_iter(t_ft_vector *vector);
void				ft_vector_iter_reset(t_ft_vector *vector);
void				*ft_vector_iter_value(t_ft_vector *vector);
void				ft_vector_iter_increment(t_ft_vector *vector);
t_ft_vector_errors	ft_vector_get_error(t_ft_vector *vector);
void				ft_vector_remove_at(t_ft_vector *vector, size_t i);
void				ft_vector_remove_last(t_ft_vector *vector);
void				ft_vector_remove_first(t_ft_vector *vector);
void				ft_vector_hex_print(t_ft_vector *vector);

#endif
