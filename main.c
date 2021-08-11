/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atawana <atawana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 11:34:15 by atawana           #+#    #+#             */
/*   Updated: 2021/08/11 12:56:24 by atawana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_functions/main_functions.h"

int	main(int c, char **argv, char **envp)
{
	(void)c;
	int i = 0;
	while (envp[i])
	{
		printf("ENVP ADDR: %p\n", envp[i++]);
	}
	startup_init(argv, envp);
	while (1)
	{
		input_loop();
	}
	free(get_status()->home);
	return (0);
}
