/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:40:30 by pcosta-j          #+#    #+#             */
/*   Updated: 2020/07/16 17:39:58 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((48 <= c && c <= 57) || (97 <= c && c <= 122) || (65 <= c && c <= 90))
		return (1);
	else
		return (0);
}
