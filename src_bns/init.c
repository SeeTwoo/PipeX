/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:51:57 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 22:11:51 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**get_pipes(int size)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (size + 1));
	i = 0;
	while (i < size)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (free_pipes(pipes, i));
		if (pipe(pipes[i]) == -1)
			return (free_pipes(pipes, i));
		i++;
	}
	pipes[i] = NULL;
	return (pipes);
}

void	init(t_args *args, int ac, char **av, char **envp)
{
	args->hd_status = heredoc_status(av);
	args->command_number = get_command_number(ac, av);
	if (args->hd_status == 1)
	{
		args->in = heredoc(av[2]);
		args->out = open(av[ac -1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		args->in = open(av[1], O_RDONLY);
		args->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
}
