/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:21 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 12:51:47 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_args	*args;

	if (ac != 5)
		return (0);
	args = NULL;
	init(&args, ac, av, envp);
	ft_printf("%spaths are :%s\n\n", BYELLOW, RESET);
	print_double_array(args->paths);
	ft_printf("%sfds are :%s\n\n", BYELLOW, RESET);
	print_int_array(args->fds, 4);
	clean(args);
	return (0);
}
