/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 23:01:35 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:15:35 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void	print_vector_error(const char *str)
{
	if (LOG_ERRORS)
	{
		ft_putstr_fd("[ERROR]: ", 1);
		ft_putstr_fd((char *)str, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	*at(t_ft_vector *vector, size_t i)
{
	void		*result;

	if (i < vector->size)
		result = vector->data + (vector->element_size * i);
	else
	{
		print_vector_error("ft vector out of range");
		vector->error = OUT_OF_RANGE;
		result = 0;
	}
	return (result);
}

void	ft_vector_add(t_ft_vector *vector, void *data)
{
	void	*new_element_addr;

	if (vector->allocated <= vector->size)
	{
		ft_vector_reallocate(vector);
		if (vector->error == NO_ERROR)
			ft_vector_add(vector, data);
		return ;
	}
	new_element_addr = (vector->size * vector->element_size) + vector->data;
	ft_memcpy(new_element_addr, data, vector->element_size);
	vector->size++;
}
