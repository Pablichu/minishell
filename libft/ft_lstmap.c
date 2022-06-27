/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:36:59 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/06/02 10:14:41 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*middle;
	t_list	*temp;
	t_list	*lista;

	if (lst)
	{
		temp = lst;
		lista = ft_lstnew(f(temp->content));
		if (!lista)
			return (NULL);
		temp = temp->next;
		while (temp)
		{
			middle = ft_lstnew(f(temp->content));
			if (!middle)
			{
				ft_lstclear(&lista, del);
				return (NULL);
			}
			ft_lstadd_back(&lista, middle);
			temp = temp->next;
		}
		return (lista);
	}
	return (NULL);
}
