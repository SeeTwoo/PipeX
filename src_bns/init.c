/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:51:57 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/03 12:30:09 by walter           ###   ########.fr       */
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

int	**get_pipes(int size)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * (size + 1));
	if (!pipes)
		return (NULL);
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

void	heredoc_init(t_args *args, int ac, char **av, char **envp)
{
	args->hd_status = 1;
	args->ac = ac;
	args->paths = get_path(envp);
	args->command_number = ac - 4;
	args->commands = &av[3];
	args->in = heredoc(av[2]);
	args->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	init(t_args *args, int ac, char **av, char **envp)
{
	args->hd_status = 0;
	args->ac = ac;
	args->paths = get_path(envp);
	args->command_number = ac - 3;
	args->commands = &av[2];
	args->in = open(av[1], O_RDONLY);
	args->out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}
