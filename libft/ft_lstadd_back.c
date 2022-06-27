/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:56:34 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/10/04 20:56:37 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
			new->next = NULL;
			return ;
		}
		else
		{
			list = ft_lstlast(*lst);
			list->next = new;
			new->next = NULL;
		}
	}
}
