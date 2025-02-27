/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:51:57 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 14:43:21 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	*get_fds(int ac, char **av, int command_number)
{
	int		*fds;
	int		i;

	fds = malloc(sizeof(int) * (command_number * 2));
	if (!fds)
		return (NULL);
	i = 0;
	while (i < command_number * 2)
		fds[i++] = -1;
	fds[0] = open(get_infile(av), O_RDONLY);
	i = 0;
	while (i < command_number)
		pipe(&fds[i++ * 2]);
	fds[(i * 2) - 1] = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT);
	return (fds);
}

void	init(t_args **args, int ac, char **av, char **envp)
{
	*args = malloc(sizeof(t_args));
	if (!args)
		fail(*args, "malloc trouble: ", "try again and hope for the best\n");
	(*args)->command_number = get_command_number(ac, av);
	(*args)->paths = ft_split(get_path(envp), ":");
	(*args)->command = NULL;
	(*args)->fds = get_fds(ac, av, (*args)->command_number);
	if (!(*args)->fds)
		fail(*args, "init failed: ", "try again and hope for the best\n");
}
