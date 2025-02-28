/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:21 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/28 14:55:00 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_args	*args;

	if (ac < 5)
		return (0);
	args = NULL;
	init(&args, ac, av, envp);
	pipeline(args, get_first_command(av, args->hd_status));
	clean(args);
	return (0);
}
