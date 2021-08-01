/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 23:53:52 by atawana           #+#    #+#             */
/*   Updated: 2021/04/18 14:34:28 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_FT_VECTOR_H
# define MINIRT_FT_VECTOR_H

# include "libft.h"

# define LOG_ERRORS 1

typedef enum			e_ft_vector_errors
{
	NO_ERROR, MALLOC_ERROR, OUT_OF_RANGE, INVALID_ITERATOR
}						t_ft_vector_errors;

struct s_ft_vector;

typedef void(*t_f_ptr)(struct s_ft_vector *);

typedef struct			s_ft_vector
{
	void				*data;
	size_t				element_size;
	size_t				allocated;
	size_t				size;
	t_f_ptr				special_free;
	void				*iterator;
	size_t				iterator_idx;
	t_ft_vector_errors	error;
}						t_ft_vector;

void					ft_vector_reallocate(t_ft_vector *vector);
void					ft_vector_add(t_ft_vector *vector, void *data);
void					ft_vector_init(t_ft_vector *vector, size_t elem_size);
void					ft_vector_set_special_free(t_ft_vector *v, t_f_ptr f);
void					*at(t_ft_vector *vector, size_t i);
void					print_vector_error(const char *str);
void					*ft_vector_iter(t_ft_vector *vector);
void					ft_vector_iter_reset(t_ft_vector *vector);
void					*ft_vector_iter_value(t_ft_vector *vector);
void					ft_vector_iter_increment(t_ft_vector *vector);
t_ft_vector_errors		ft_vector_get_error(t_ft_vector *vector);
void					ft_vector_remove_at(t_ft_vector *vector, size_t i);
void					ft_vector_remove_last(t_ft_vector *vector);
void					ft_vector_remove_first(t_ft_vector *vector);
void					ft_vector_hex_print(t_ft_vector *vector);

#endif
