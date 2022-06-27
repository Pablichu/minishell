/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 17:45:57 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/01/26 19:47:16 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**Devuelve una copia de s1 sin los caracteres de set ni al principio ni al final
**
** - Si no hay set o s1, devuelve NULL
** - Si hay s1 (tenemos información en ese carácter), y además ese carácter se
** encuentra en set, avanza en la dirección de memoria de s1. Lo que hace es ir
** avanzando en la dirección de memoria de s1 hasta que encuentra un carácter
** que no coincide con los que hay en set, y ahí se para
** - Hallamos la longitud de la cadena resultante de avanzar en s1, es decir, lo
** que mide quitando los caracteres que si que están en set (s1_len)
** - Mientras s1_len != 0 y el carácter de s1 en la última posición de la cadena
** esté en set, disminuye s1_len. Básicamente lo que hago es que empiezo por
** el final de la cadena comprobando si está el último carácter en set, y voy
** retrocediendo hasta que encuentro un carácter que no está, y me quedo con la
** longitud final de la cadena
** - Utilizo ft_substr para devolver una cadena que empieza en la posición 0 de
** s1 (porque ya he quitado los caracteres que no coinciden del principio) con
** longitud s1_len + 1 (+1 para el final de cadena)
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s1_len;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	s1_len = ft_strlen(s1);
	while (s1_len && ft_strchr(set, s1[s1_len]))
		s1_len--;
	new = ft_substr((char *)s1, 0, s1_len + 1);
	return (new);
}
