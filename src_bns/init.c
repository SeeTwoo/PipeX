/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:51:57 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 18:53:19 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init(t_args **args, int ac, char **av, char **envp)
{
	*args = malloc(sizeof(t_args));
	if (!args)
		fail(*args, "malloc trouble: ", "try again and hope for the best\n");
	(*args)->hd_status = heredoc_status(av);
	(*args)->command_number = get_command_number(ac, av);
	(*args)->paths = ft_split(get_path(envp), ":");
	(*args)->command = NULL;
}
