/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freee.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:44:08 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/11 20:48:49 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//If ft_freee does not work well
//it probably be because of NOT NULL at matrix end

void	ft_freee(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i])
		i++;
	j = 0;
	while (j <= i)
	{
		free(matrix[j]);
		j++;
	}
	free(matrix);
}
