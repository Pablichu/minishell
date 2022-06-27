/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 16:02:06 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:07:34 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned	int, char))
{
	char	*new;
	int		i;
	int		n;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
