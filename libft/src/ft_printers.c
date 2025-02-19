/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbeschon <wbeschon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:51:31 by wbeschon          #+#    #+#             */
/*   Updated: 2025/02/06 17:00:58 by wbeschon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (*s)
	{
		i += ft_putchar(*s);
		s++;
	}
	return (i);
}

int	ft_putnbr(long long n)
{
	int		len;
	int		i;
	char	dest[11];

	len = 0;
	i = 0;
	if (n < 0)
	{
		i += ft_putchar('-');
		n = -n;
	}
	while (n > 9)
	{
		dest[len] = (n % 10) + '0';
		len++;
		n /= 10;
	}
	dest[len] = n + '0';
	while (len >= 0)
	{
		i += ft_putchar(dest[len]);
		len--;
	}
	return (i);
}

int	ft_puthex(unsigned int n, char *base)
{
	int	i;

	i = 0;
	if (n > 15)
	{
		i += ft_puthex(n / 16, base);
		i += ft_putchar(base[n % 16]);
	}
	else
		i += ft_putchar(base[n]);
	return (i);
}

int	ft_putptr(void *ptr)
{
	int				i;
	unsigned long	address;

	i = 0;
	address = (unsigned long)ptr;
	if (!ptr)
		return (ft_putstr("(nil)"));
	i += ft_putstr("0x");
	i += ft_putlhex(address, "0123456789abcdef");
	return (i);
}
