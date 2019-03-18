/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa_base.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/25 21:27:11 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/03/18 11:07:09 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		len_size(long nb, int base)
{
	int len;

	len = 0;
	if (nb < 0)
	{
		nb *= -1;
		if (base == 10)
			len++;
	}
	while (nb > 0)
	{
		nb /= base;
		len++;
	}
	return (len);
}

char			*itoa_base(int nb, int base)
{
	int		len;
	long	nbr;
	char	*str;

	if (base < 2 || base > 16)
		return (NULL);
	nbr = (long)nb;
	len = len_size(nbr, base);
	str = (char*)malloc(sizeof(char) * len + 1);
	str[len--] = '\0';
	if (nbr < 0)
	{
		nbr *= -1;
		if (base == 10)
			str[0] = '-';
	}
	while (len >= 0)
	{
		str[len--] = "0123456789ABCDEF"[nbr % base];
		nbr /= base;
		if (str[len] == '-')
			break ;
	}
	return (str);
}
