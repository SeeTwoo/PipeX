/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:46:25 by wbeschon          #+#    #+#             */
/*   Updated: 2025/03/04 11:43:43 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_command_path(char *s, char *paths)
{
	char	*temp;
	char	*token;
	char	*paths_dup;
	char	*current_path;

	paths_dup = ft_strdup(paths);
	temp = ft_strjoin("/", s);
	if (!temp || !paths_dup)
		return (free(paths_dup), free(temp), NULL);
	token = ft_strtok(paths_dup, ":");
	while (token)
	{
		current_path = ft_strjoin(token, temp);
		if (access(current_path, X_OK) == 0)
			return (free(paths_dup), free(temp), current_path);
		free(current_path);
		token = ft_strtok(NULL, ":");
	}
	free(temp);
	free(paths_dup);
	return (ft_strdup(s));
}

char	**get_command(char *s, char *paths)
{
	char	**command;
	char	*command_path;

	if (!s[0])
		return (NULL);
	command = ft_split(s, " ");
	if (!command)
		return (NULL);
	if (command[0][0] == '/' || !paths)
		return (command);
	command_path = get_command_path(command[0], paths);
	if (!command_path)
	{
		free_double_array(command);
		return (NULL);
	}
	free(command[0]);
	command[0] = command_path;
	return (command);
}
