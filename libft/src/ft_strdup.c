/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:45:19 by wbeschon          #+#    #+#             */
/*   Updated: 2024/11/29 11:51:14 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, ft_strlen(s) + 1);
	return (dest);
}

/*#include <stdio.h>
int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);

	char	*dest1;
	char	*dest2;
	dest1 = ft_strdup(av[1]);
	dest2 = strdup(av[1]);
	printf("%s\n", dest1);
	printf("%s\n", dest2);
	free(dest1);
	free(dest2);
	return (0);
}
*/
