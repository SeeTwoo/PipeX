/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:50:11 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/03 21:31:26 by walter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_double_array(char **array)
{
	int	i;

	if (!array)
		return ;
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

void	close_all(t_args *args)
{
	int	i;

	if (args->in != -1)
		close(args->in);
	if (args->out != -1)
		close(args->out);
	if (!args->pipes)
		return ;
	i = 0;
	while (i < args->command_number - 1)
	{
		if (args->pipes[i][0] != -1)
			close(args->pipes[i][0]);
		if (args->pipes[i][1] != -1)
			close(args->pipes[i][1]);
		i++;
	}
}

void	clean(t_args *args)
{
	close_all(args);
	free_pipes(args->pipes, args->command_number - 1);
	args->pipes = NULL;
	free(args->pids);
	args->pids = NULL;
}

void	error(char *msg1, char *msg2, t_args *args)
{
	clean(args);
	ft_error_msg(msg1, msg2);
	exit(EXIT_FAILURE);
}
