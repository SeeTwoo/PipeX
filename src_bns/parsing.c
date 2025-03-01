/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:46:25 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/28 16:58:23 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_command_path(char *s, char **paths)
{
	char	*temp;
	char	*current_path;

	if (!paths || access(s, X_OK) == 0)
		return (s);
	temp = ft_strjoin("/", s);
	if (!temp)
		return (s);
	while (*paths)
	{
		current_path = ft_strjoin(*paths, temp);
		if (access(current_path, X_OK) == 0)
			return (current_path);
		free(current_path);
		paths++;
	}
	free(temp);
	return (s);
}

char	**get_command(char *s, char **paths)
{
	char	**command;
	char	*command_path;

	command = ft_split(s, " ");
	command_path = get_command_path(command[0], paths);
	free(command[0]);
	command[0] = command_path;
	return (command);
}

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
