/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:51:57 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/01 14:10:22 by wbeschon         ###   ########.fr       */
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
		fail(*args, "malloc trouble: ", "try again and hope for the best\n");
	(*args)->hd_status = heredoc_status(av);
	(*args)->command_number = get_command_number(ac, av);
	(*args)->paths = ft_split(get_path(envp), ":");
	(*args)->command = NULL;
	(*args)->pipes = get_pipes((*args)->command_number -1);
	(*args)->pids = ft_calloc((*args)->command_number, sizeof(int));
	(*args)->in = get_in_fd(*args, ac, av);
	(*args)->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!(*args)->pipes)
		fail(*args, "pipes failed", NULL);
	if (!(*args)->pids)
		fail(*args, "malloc trouble: ", "try again and hope for the best\n");
}
