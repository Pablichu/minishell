/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 18:42:41 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/08/14 00:21:55 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(s);
	if (c == 0)
		return ((void *)(s + n));
	while (i < n)
	{
		if (s[i] == c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
