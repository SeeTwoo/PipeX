/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:08:07 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/25 16:51:28 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_command_path(char *command, char **paths)
{
	char	*current_path;
	char	*temp;

	if (access(command, X_OK) == 0)
		return (command);
	temp = ft_strjoin("/", command);
	if (!temp)
		return (NULL);
	while (*paths)
	{
		current_path = ft_strjoin(*paths, temp);
		if (access(current_path, X_OK) == 0)
		{
			free(temp);
			return (current_path);
		}
		paths++;
		free(current_path);
		current_path = NULL;
	}
	free(temp);
	return (command);
}

void	get_command(t_args *args, int i)
{
	char	*command_path;

	args->command = ft_split(args->av[i + 2], " ");
	command_path = get_command_path(args->command[0], args->paths);
	if (!command_path)
	{
		free_double_array(args->command);
		return ;
	}
	args->command[0] = command_path;
}

char	*get_path(char **envp)
{
	char	*path;
	int		i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	path = &envp[i][5];
	return (path);
}

void	parsing(int ac, char **av, char **envp, t_args *args)
{
	args = malloc(sizeof(t_args));
	if (!args || ac != 5)
		return ; 
	args->ac = ac;
	args->av = av;
	args->paths = ft_split(get_path(envp), ":");
	args->command = NULL;
	if (!args->paths)
	{
		clean(args);
		return ;
	}
}
