/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:51:57 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 15:48:24 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_in_fd(t_args *args, int ac, char **av)
{
	(void)ac;
	if (args->hd_status == 0)
		return (open(av[1], O_RDONLY));
	else
		return (heredoc(av[2]));
}

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

void	init(t_args **args, int ac, char **av, char **envp)
{
	*args = malloc(sizeof(t_args));
	if (!args)
		fail(*args, "PipeX");
	(*args)->hd_status = heredoc_status(av);
	if ((*args)->hd_status == 1)
		(*args)->in = heredoc(av[2]);
	(*args)->command_number = get_command_number(ac, av);
	(*args)->paths = ft_split(get_path(envp), ":");
	(*args)->command = NULL;
	(*args)->pipes = get_pipes((*args)->command_number -1);
	(*args)->pids = ft_calloc((*args)->command_number, sizeof(int));
	if (!(*args)->pipes)
		fail(*args, "PipeX");
	if (!(*args)->pids)
		fail(*args, "PipeX");
}
