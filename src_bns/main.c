/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:21 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 16:17:09 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	usage(int ac, char **av)
{
	if (ac < 6 && av[1] && ft_strcmp(av[1], "here_doc") == 0)
	{
		ft_printf("Usage: ./pipex_bonus here_doc <LIMITER> <\"cmd1\"> <\"cmd2\">");
		ft_printf(" ... <\"cmdn\"> <outfile>\n");
		exit(EXIT_FAILURE);
	}
	else if (ac < 5)
	{
		ft_printf("Usage: ./pipex_bonus <infile> <\"cmd1\"> <\"cmd2\"> ...");
		ft_printf(" <\"cmdn\"> <outfile>\nOr: ./pipex_bonus here_doc <LIMITER>");
		ft_printf(" <\"cmd1\"> <\"cmd2\"> ... <\"cmdn\"> <outfile>\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_args	*args;

	args = NULL;
	usage(ac, av);
	init(&args, ac, av, envp);
	pipeline(args, get_first_command(av, args->hd_status));
	clean(args);
	return (0);
}
