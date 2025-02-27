/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:46:25 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 12:56:28 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path(char **envp)
{
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

char	*get_infile(char **av)
{
	return (av[1]);
}
