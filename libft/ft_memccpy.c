/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:19:40 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:13:08 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*destino;
	const unsigned char	*fuente;
	size_t				i;

	i = 0;
	destino = (unsigned char *)dest;
	fuente = (unsigned char *)src;
	while (i < n)
	{
		destino[i] = fuente[i];
		if (fuente[i] == (unsigned char)c)
			return ((void *)(destino + i + 1));
		i++;
	}
	return (NULL);
}
