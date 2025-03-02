/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:50:11 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 13:08:31 by wbeschon         ###   ########.fr       */
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
		//free(array[i++]);

int	**free_pipes(int **pipes, int i)
{
	if (!pipes)
		return (NULL);
	while (i >= 0)
		free(pipes[i--]);
	free(pipes);
	return (NULL);
}

void	clean(t_args *args)
{
	if (!args)
		return ;
	close_all(args);
	if (args->paths)
		free_double_array(args->paths);
	if (args->command)
		free_double_array(args->command);
	if (args->pipes)
		free_pipes(args->pipes, args->command_number - 1);
	if (args->pids)
		free(args->pids);
	free(args);
}

void	close_all(t_args *args)
{
	int	i;

	close(args->in);
	close(args->out);
	i = 0;
	while (args->pipes[i])
	{
		close(args->pipes[i][0]);
		close(args->pipes[i][1]);
		i++;
	}
}

void	fail(t_args *args, char *msg)
{
	if (msg)
		perror(msg);
	clean(args);
	exit(EXIT_FAILURE);
}
