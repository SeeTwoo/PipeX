/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:54:44 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/02 16:32:05 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	heredoc_status(char **av)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		return (1);
	return (0);
}

int	heredoc(char *limiter)
{
	int		hd_pipe[2];
	char	*lim;
	char	*line;

	if (pipe(hd_pipe) == -1)
		return (-1);
	lim = ft_strjoin(limiter, "\n");
	if (!lim)
		return (-1);
	while (1)
	{
		ft_putstr_fd("\rheredoc> ", 1);
		line = get_next_line(0);
		if (ft_strcmp(line, lim) != 0)
			ft_putstr_fd(line, hd_pipe[1]);
		else
			break ;
		free(line);
	}
	free(lim);
	free(line);
	close(hd_pipe[1]);
	return (hd_pipe[0]);
}
