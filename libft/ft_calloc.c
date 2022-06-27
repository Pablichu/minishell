/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:20:49 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:16:24 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned int	space;
	void			*cadena;

	space = nmemb * size;
	cadena = malloc(space);
	if (!cadena)
		return (NULL);
	ft_bzero(cadena, space);
	return (cadena);
}
