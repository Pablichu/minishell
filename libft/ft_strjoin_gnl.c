/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:11:52 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:08:06 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char			*new;
	unsigned int	n;
	unsigned int	m;
	unsigned int	i;
	unsigned int	j;

	n = ft_strlen(s1);
	m = ft_strlen(s2);
	new = malloc(n + m + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = -1;
	while (i < n)
	{
		new[i] = s1[i];
		i++;
	}
	while (++j < m)
		new[j + i] = s2[j];
	new[j + i] = '\0';
	return (new);
}
