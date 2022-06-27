/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:12:12 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:15:55 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	len_num(long int n)
{
	int		i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char
	*ft_itoa(int n)
{
	int				i;
	char			*cadena;
	long int		ln;

	ln = n;
	i = len_num(ln);
	cadena = (malloc(sizeof(char) * (i + 1)));
	if (!cadena)
		return (NULL);
	cadena[i--] = '\0';
	cadena[0] = '0';
	if (ln < 0)
	{
		cadena[0] = '-';
		ln = ln * -1;
	}
	while (ln > 0)
	{
		cadena[i] = '0' + (ln % 10);
		ln = ln / 10;
		i--;
	}
	return (cadena);
}
