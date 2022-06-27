/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 16:01:21 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:12:37 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;
	int	n;

	if (!s)
		return ;
	i = 0;
	n = ft_strlen(s);
	while (i < n)
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
