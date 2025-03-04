/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:21 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/04 11:02:35 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_args	args;

	if (ac != 5)
	{
		ft_printf("Usage: ./pipex_bonus <infile> <\"cmd1\"> <\"cmd2\"> ");
		ft_printf("<outfile>");
		exit(EXIT_FAILURE);
	}
	init(&args, ac, av, envp);
	pipeline(&args);
	return (0);
}
