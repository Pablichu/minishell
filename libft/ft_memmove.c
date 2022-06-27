/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:18:45 by pcosta-j          #+#    #+#             */
/*   Updated: 2020/07/31 19:17:32 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*destino;
	const char		*fuente;
	unsigned int	i;

	destino = dest;
	fuente = src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (fuente > destino)
	{
		while (i < n)
		{
			destino[i] = fuente[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			destino[i] = fuente[i];
	}
	return (destino);
}
