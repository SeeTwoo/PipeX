/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:09:48 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/19 18:22:46 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**free_double_array(char **tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
		ft_printf("lap\n");
	}
	free(tab);
	return (NULL);
}

t_args	*free_args(t_args *args)
{
	if (args->paths)
		free_double_array(args->paths);
	if (args->command)
		free_double_array(args->paths);
	free(args);
	return (NULL);
}

void	close_tab(int *tab, size_t size)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (i < size)
	{
		close(tab[i]);
		i++;
	}
}
