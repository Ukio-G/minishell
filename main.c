/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:34:15 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 12:01:40 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_functions/main_functions.h"

int	main(int argc, char **argv, char **envp)
{
	startup_init(argv, envp);
	while (1)
	{
		input_loop();
	}
	free(get_status()->home);
	return (0);
}
