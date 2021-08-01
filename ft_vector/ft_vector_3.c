/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 23:02:02 by atawana           #+#    #+#             */
/*   Updated: 2021/03/27 23:52:47 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void		ft_vector_init(t_ft_vector *vector, size_t elem_size)
{
	vector->allocated = 0;
	vector->size = 0;
	vector->data = 0;
	vector->special_free = 0;
	vector->element_size = elem_size;
	ft_vector_reallocate(vector);
	ft_bzero(vector->data, vector->allocated * vector->element_size);
	ft_vector_iter_reset(vector);
}

void		ft_vector_free(t_ft_vector *vector)
{
	if (vector->special_free != 0)
		vector->special_free(vector);
	vector->allocated = 0;
	vector->size = 0;
	if (vector->data)
		free(vector->data);
	vector->data = 0;
}

void		ft_vector_remove_at(t_ft_vector *vector, size_t i)
{
	void	*dst;
	void	*src;
	size_t	size;

	if (i < vector->size)
	{
		if (i + 1 < vector->size)
		{
			dst = vector->data + (i * vector->element_size);
			src = dst + vector->element_size;
			size = (vector->size - i) * vector->element_size;
			ft_memmove(dst, src, size);
		}
		vector->size--;
		src = vector->data + (vector->size) * vector->element_size;
		ft_bzero(src, vector->element_size);
	}
	else
	{
		print_vector_error("ft vector try remove non existing element");
		vector->error = OUT_OF_RANGE;
	}
}

void		ft_vector_remove_last(t_ft_vector *vector)
{
	ft_vector_remove_at(vector, vector->size - 1);
}

void		ft_vector_remove_first(t_ft_vector *vector)
{
	ft_vector_remove_at(vector, 0);
}
