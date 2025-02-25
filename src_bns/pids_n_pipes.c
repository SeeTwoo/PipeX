/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids_n_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:12:38 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 17:33:46 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	*close_pipes(int *pipefd, int pipe_nb)
{
	int	i;

	if (!pipefd)
		return (NULL);
	i = 0;
	while (i < pipe_nb * 2)
		if (pipefd[i++] != -1)
			close(pipefd[i]);
	free(pipefd);
	return (NULL);
}

int	*create_pipes(t_args *args)
{
	int	i;

	args->pipe_nb = ac - 4;
	args->pipefd = malloc(sizeof(int) * ((args->pipe_nb * 2) + 2));
	if (!args->pipefd)
		return (NULL);
	i = 0;
	while (i < ((args->pipe_nb * 2) + 2))
		args->pipefd[i++] = -1;
	args->pipefd[0] = open(args->av[1], O_RDONLY);
	i = 1;
	while (i < args->pipe_nb)
		if (pipe(&(args->pipefd)[i++ * 2]) == -1)
			return (close_pipes(args->pipefd, args->pipe_nb));					//some free later
	args->pipefd[(i * 2) + 1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT);
	return (pipefd);
}

void	wait_pids(int *pids, int pid_nb)
{
	int	i;

	if (!pids)
		return ;
	i = 0;
	while (i < pid_nb)
		waitpid(pids[i++], NULL, 0);
}

int	*create_pids(int *pids, int *pid_nb, int ac)
{
	*pid_nb = ac - 3;
	pids = malloc(sizeof(pid_t) * *pid_nb);
	if (!pids)
		return (NULL);
	return (pids);
}
