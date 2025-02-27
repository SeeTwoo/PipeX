/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:50:11 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 13:05:52 by wbeschon         ###   ########.fr       */
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

void	clean(t_args *args)
{
	if (!args)
		return ;
	if (args->paths)
		free_double_array(args->paths);
	if (args->command)
		free_double_array(args->command);
	if (args->fds)
		free(args->fds);
	free(args);
}

void	fail(t_args *args, char *msg1, char *msg2)
{
	clean(args);
	perror(REDBG);
	perror("PipeX:");
	perror(RESET);
	perror(msg1);
	perror(msg2);
	exit(EXIT_FAILURE);
}
