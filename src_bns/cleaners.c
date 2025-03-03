/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:50:11 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/03 11:38:50 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	**free_pipes(int **pipes, int i)
{
	if (!pipes)
		return (NULL);
	while (i >= 0)
		free(pipes[i--]);
	free(pipes);
	return (NULL);
}

void	close_all(t_args *args, int **pipes)
{
	int	i;

	close(args->in);
	close(args->out);
	i = 0;
	while (i < args->command_number - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
