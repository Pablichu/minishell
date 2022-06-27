/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:19:11 by pcosta-j          #+#    #+#             */
/*   Updated: 2020/07/31 19:17:07 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destino;
	const char	*fuente;
	size_t		i;

	i = 0;
	destino = dest;
	fuente = src;
	if (!destino && !fuente)
		return (NULL);
	while (i < n)
	{
		destino[i] = fuente[i];
		i++;
	}
	return (dest);
}
