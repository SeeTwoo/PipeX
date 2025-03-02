/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:51:57 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 23:23:36 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **envp)
{
	if (!envp[0])
		return (NULL);
	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!(*envp))
		return (NULL);
	return (&((*envp)[5]));
}

int	get_command_number(int ac, char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (ac - 4);
	else
		return (ac - 3);
}

char	**get_first_command(char **av, int hd_status)
{
	if (hd_status == 1)
		return (&av[3]);
	return (&av[2]);
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

void	init(t_args *args, int ac, char **av, char **envp)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
		args->hd_status = 1;
	else
		args->hd_status = 0;
	args->command_number = get_command_number(ac, av);
	args->ac = ac;
	args->commands = get_first_command(av, args->hd_status);
	args->paths = get_paths(envp);
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
