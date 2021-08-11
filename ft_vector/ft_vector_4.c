/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 23:10:34 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 03:16:07 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

t_ft_vector_errors	ft_vector_get_error(t_ft_vector *vector)
{
	t_ft_vector_errors	result;

	result = vector->error;
	vector->error = NO_ERROR;
	return (result);
}
