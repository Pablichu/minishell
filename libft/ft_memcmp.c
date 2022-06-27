/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 19:01:20 by pcosta-j          #+#    #+#             */
/*   Updated: 2020/07/22 17:22:03 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	const char		*cadena1;
	const char		*cadena2;

	cadena1 = s1;
	cadena2 = s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((cadena1[i] == cadena2[i]) && (i < n - 1))
		i++;
	return ((unsigned char)cadena1[i] - (unsigned char)cadena2[i]);
}
