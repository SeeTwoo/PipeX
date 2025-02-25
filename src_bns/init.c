/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:51:58 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 17:16:16 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_var(t_args *args)
{
	args->ac = 0;
	args->av = NULL;
	args->paths = NULL;
	args->command = NULL;
	args->pipefd = NULL;
	args->pipe_nb = 0;
	args->pids = NULL;
	args->pid_nb = 0;
}

int	init(t_args *args, int ac, char **av, char **envp)
{
	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	init_var(args);
	parsing(ac, av, envp, args);
	if (!create_pipes(args->pipefd, args->pipe_nb, args->ac, args->av))
		fail(args); 
	if (!create_pids(args->pids, args->pid_nb, args->ac))
		fail(args); 
	return (0);
}
