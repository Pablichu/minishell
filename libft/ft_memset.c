/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:18:00 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/03/03 13:56:40 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*cadena;
	char			car;
	size_t			i;

	cadena = s;
	car = c;
	i = 0;
	while (i < n)
	{
		cadena[i] = car;
		i++;
	}
	return (cadena);
}
