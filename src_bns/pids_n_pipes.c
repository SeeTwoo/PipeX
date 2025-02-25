/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids_n_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 08:12:38 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 13:28:10 by wbeschon         ###   ########.fr       */
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

int	*create_pipes(int *pipefd, int *pipe_nb, int ac, char **av)
{
	int	i;

	*pipe_nb = ac - 4;
	pipefd = malloc(sizeof(int) * ((pipe_nb * 2) + 2))
	if (!pipefd)
		return (NULL);
	i = 0;
	while ((i < (*pipe_nb * 2) + 2)
		pipefd[i++] = -1;
	pipefd[0] = open(av[1], O_RDONLY);
	i = 1;
	while ((i < *pipe_nb)
		if (pipe(&pipefd[i++ * 2]) == -1)
			return (close_pipes(pipefd, *pipe_nb);								//some free later
	pipefd[(i * 2) + 1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT)
	return (pipefd);
}

void	wait_pids(int *pids, int pid_nb)
{
	int	i;

	i = 0;
	while (i < pid_nb)
		wait_pid(pids[i++]);
}

int	*create_pids(int *pids, int *pid_nb, int ac)
{
	*pid_nb = ac - 3;
	pids = malloc(sizeof(pid_t) * *pid_nb);
	if (!pids)
		return (NULL);
	return (pids);
}
