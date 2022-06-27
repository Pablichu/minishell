/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 20:14:52 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/05/28 19:04:10 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** - Guardo en new lo que haya en buff a partir del primer \n
** - Si hay \n:
** 		- Calculo longitud a partir del salto de línea
** 		- Cambio /n por /0. Como cambio en new lo que almacena esa
** 		dirección de memoria, buff también se ve afectado por ese cambio
** 		- Así strjoin reconoce \n (ahora \0 como fin de cadena), y
** 		concatena line con buff hasta \0
** 		- Libero *line tras el strjoin
** 		(*line=NULL porque si no con free ponía caracteres raros)
** 		- Guardo en *line lo que tenía antes + lo que ha leído hasta \n
** 		- Avanzo posición en new, para quitarme \n (convertido a \0),
** 		y lo guardo en la vble estática
** 		- Devuelvo 1, porque el programa está devolviendo una línea
** - Si no hay \n, añado a *line lo que hay en buff, y dejo vacía buff
** para siguiente lectura
*/

int	check_buffer(char **line, char *buff)
{
	char	*new;
	char	*aux;
	int		len_extra;

	new = ft_strchr(buff, '\n');
	if (new)
	{
		len_extra = ft_strlen(new);
		*new = '\0';
		aux = ft_strjoin_gnl(*line, buff);
		free(*line);
		*line = aux;
		ft_memmove(buff, new + 1, len_extra);
		return (1);
	}
	else
	{
		aux = ft_strjoin_gnl(*line, buff);
		free(*line);
		*line = aux;
		buff[0] = '\0';
		return (0);
	}
}

/*
** - Compruebo los casos donde puede fallar
** - Reservo espacio para line
** - En la primera llamada no tiene que haber nada en line
** - Compruebo si había \n, y si lo hay devuelvo 1, y en *line tengo la línea
** - Si no hay \n, mientras no haya EOF:
**    - Leo fichero
**    - Añado fin de cadena a lo leído
**    - Llamo de nuevo a la función que trata el buffer
*/

int	get_next_line(int fd, char **line)
{
	static char		buffer[256][BUFFER_SIZE + 1];
	int				read_file;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	*line = (char *)malloc(sizeof(char) * 1);
	if (!*line)
		return (-1);
	**line = '\0';
	read_file = BUFFER_SIZE;
	if (check_buffer(line, buffer[fd]) == 1)
		return (1);
	else
	{
		while (read_file == BUFFER_SIZE)
		{
			read_file = read(fd, buffer[fd], BUFFER_SIZE);
			if (read_file == -1)
				return (-1);
			buffer[fd][read_file] = '\0';
			if (check_buffer(line, buffer[fd]) == 1)
				return (1);
		}
	}
	return (0);
}
