/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 23:42:49 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:15:05 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	ft_vector_reallocate(t_ft_vector *vector)
{
	void	*new_data;
	size_t	new_size;
	size_t	old_size;

	old_size = vector->allocated * vector->element_size;
	if (old_size == 0)
		new_size = 10 * vector->element_size;
	else
		new_size = old_size * 2;
	new_data = malloc(new_size);
	if (!new_data)
	{
		print_vector_error("ft vector malloc error");
		vector->error = MALLOC_ERROR;
		return ;
	}
	if (vector->data)
	{
		ft_memcpy(new_data, vector->data, old_size);
		ft_bzero((new_data + old_size), new_size - old_size);
		free(vector->data);
	}
	vector->allocated = new_size / vector->element_size;
	vector->data = new_data;
}

void	ft_vector_iter_reset(t_ft_vector *vector)
{
	if (vector->size > 0)
		vector->iterator = vector->data;
	else
		vector->iterator = 0;
	vector->iterator_idx = 0;
}

void	ft_vector_iter_increment(t_ft_vector *vector)
{
	size_t	max_idx;

	max_idx = vector->size - 1;
	if (max_idx < vector->iterator_idx + 1)
	{
		vector->iterator_idx = 0;
		vector->iterator = 0;
	}
	else
	{
		vector->iterator_idx++;
		vector->iterator += vector->element_size;
	}
}

void	*ft_vector_iter_value(t_ft_vector *vector)
{
	if (vector->iterator && vector->data)
		return (vector->iterator);
	vector->error = INVALID_ITERATOR;
	print_vector_error("Invalid iterator, or iterate with invalid data!");
	return (0);
}

void	*ft_vector_iter(t_ft_vector *vector)
{
	if (vector->data != 0 && vector->iterator == 0)
	{
		ft_vector_iter_reset(vector);
		return (vector->iterator);
	}
	ft_vector_iter_increment(vector);
	return (vector->iterator);
}
