/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:56:58 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/10/04 20:57:00 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	int		n;
	char	*cadena;

	n = ft_strlen(s);
	cadena = malloc(n + 1);
	if (!cadena)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cadena[i] = s[i];
		i++;
	}
	cadena[i] = '\0';
	return (cadena);
}
