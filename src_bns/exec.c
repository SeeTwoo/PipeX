/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:51:40 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 14:22:07 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	close_tab(fds, 2);
	execve(args->command[0], args->command, NULL);
	perror
	fail(args);
}

void	exec(t_args *args)
{
	int	i;

	i = 0;
	while (i < *(args->pipe_nb))
		exec_command(args, i++);
}
