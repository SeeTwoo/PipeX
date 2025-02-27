/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:47:44 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/27 13:21:54 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_double_array(char **array)
{
	if (!array)
		return ;
	while (*array)
	{
		ft_printf("%s\n", *array);
		array++;
	}
	ft_printf("\n");
}

void	print_int_array(int *array, int size)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		ft_printf("%d\n", array[i]);
		i++;
	}
	ft_printf("\n");
}
