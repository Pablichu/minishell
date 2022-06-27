/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 20:57:33 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/03/05 19:16:35 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** - Esta función ordena una lista según su contenido
** - Necesita de una función que le diga cuál es la comparación que es necesario
** hacer (cmp)
** - Averiguamos cuál es el último elemento de la lista
** - Igualamos current a la lista, para no perderla, puesto que vamos a avanzar
** en la dirección de memoria (nodo a nodo)
** - La variable tmp se inicializa a NULL
** - Mientras no estemos en el último nodo:
**		- Si se cumple la comparación pedida por la función de comparación
**			- Intercambiamos los contenidos del nodo actual y el siguiente
**			- Si se intercambian los valores, tmp deja de ser NULL, y toma valor
**		- Si el nodo siguiente al que estamos es el último:
**			- El último pasa a ser el actual (así hacemos que no se vuelva a
**			comprobar el último nodo, puesto que ya está colocado)
**			- Si tmp no está vacío (es decir, he hecho cambio entre los
**			contenidos), vuelvo a poner current al principio de la lista para
**			poder seguir comparando
**			- Igualo tmp a NULL
**		- Sino
**			- El nodo actual pasa a ser el siguiente, avanzo en la lista
**
** - Si la lista está ordenada no entra en la comparación, con lo cual tmp tiene
** valor NULL, y lo que hacemos es poner current al principio de la lista.
** - Con lo cual si está ordenada voy avanzando nodo a nodo en la lista, hasta
** que llega un momento que current = last y ya no compruebo más
*/

inline void
	ft_lstsort(t_list *lst, int (*cmp)())
{
	t_list	*current;
	t_list	*last;
	void	*tmp;

	last = ft_lstlast(lst);
	current = lst;
	tmp = NULL;
	while (current != last)
	{
		if (cmp(current->content, current->next->content))
		{
			tmp = current->content;
			current->content = current->next->content;
			current->next->content = tmp;
		}
		if (current->next == last)
		{
			last = current;
			if (tmp)
				current = lst;
			tmp = NULL;
		}
		else
			current = current->next;
	}
}

/*
** - Igualamos swap a la lista pasada como parámetro, para no perderla, ya que
** necesitamos ir avanzando
** - Mientras swap no sea el último nodo de la lista:
**		- Igualamos current al nodo siguiente a swap
**		- Mientras haya algo en current:
**			- Si se cumple la comparación hecha por cmp entre los contenidos de
**			swap y su siguiente nodo:
**				- Intercambiamos los valores de ese nodo y el siguiente
**		- Avanzamos al siguiente nodo (current->next = swap->next->next)
** - Avanzamos al siguiente nodo de la lista (swap->next)
**
** OJO: esta función no está optimizada, por lo que con mapas grandes va muy
** lento
** Aunque este algoritmo de ordenación es sencillo, tiene muy bajo rendimiento
**
** -Probar a optimizar: si no ha habido cambio, salimos de la función
** Esto hace que no tengamos que comprobar los contenidos de toda la lista;
** esto es así porque si no ha habido cambio, significa que ya están ordenados
** y no hace falta seguir comprobando, que es lo que haría el bubble sort
*/

/*
**inline void	ft_lstsort(t_list *lst, int (*cmp)())
**{
**	t_list	*current;
**	t_list	*swap;
**	void	*tmp;
**
**	swap = lst;
**	while (swap != ft_lstlast(lst))
**	{
**		current = swap->next;
**		while (current != NULL)
**		{
**			if (cmp(swap->content, current->content))
**			{
**				tmp = swap->content;
**				swap->content = current->content;
**				current->content = tmp;
**			}
**			current = current->next;
**		}
**		swap = swap->next;
**	}
**}
*/
