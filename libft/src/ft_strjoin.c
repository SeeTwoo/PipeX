/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:03:50 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/25 14:28:36 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s1, ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strlcat(dest, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (dest);
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	char *join;
	
	join = ft_strjoin(av[1], av[2]);
	printf("%s\n", join);
	free(join);
	return (0);
}*/
