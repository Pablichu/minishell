/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:36:08 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:12:58 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int		i;
	unsigned const char	*cadena;
	unsigned char		d;

	cadena = s;
	d = c;
	i = 0;
	while (i < n)
	{
		if (cadena[i] == d)
			return ((unsigned char *)(cadena + i));
		i++;
	}
	return (NULL);
}
