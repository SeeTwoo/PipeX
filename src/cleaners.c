/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:50:11 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/04 11:01:33 by wbeschon         ###   ########.fr       */
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

void	close_all(t_args *args)
{
	int	i;

	if (args->in != -1)
		close(args->in);
	if (args->out != -1)
		close(args->out);
	if (args->pipefd[0] != -1)
		close(args->pipefd[0]);
	if (args->pipefd[1] != -1)
		close(args->pipefd[1]);
}

void	error(char *msg1, char *msg2, t_args *args)
{
	close_all(args);
	ft_error_msg(msg1, msg2);
	exit(EXIT_FAILURE);
}
