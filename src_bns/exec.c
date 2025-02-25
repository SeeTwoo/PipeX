/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:40 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 16:26:50 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fail(t_args *args)
{
	clean(args);
	exit(EXIT_FAILURE);
}

void	exec_command(t_args *args, int i)
{
	int	*fds;

	fds = &(args->pipefd[i * 2]);
	get_command(args, i);
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[1], STDOUT_FILENO);
	close_pipes(fds, 2);
	execve(args->command[0], args->command, NULL);
	fail(args);											//add some error msg later
}

void	exec(t_args *args)
{
	int	i;

	i = 0;
	while (i < *(args->pipe_nb))
	{
		args->pids[i] = fork();
		if (args->pids[i] == 0)
			exec_command(args, i);
		i++;
	}
}
