/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 22:13:49 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 23:53:49 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** - Counting the number of words of a string with the following conditions:
**	- A word is separated by spaces, except if you find a quote (simple or
** double); all the text between quotes is a word, independently if there are
** spaces or not inside quotes
*/

int
	count_words(t_shell *mini, char *s)
{
	int	num;
	int	words;

	num = 0;
	words = 0;
	while (*s != '\0')
	{
		num = 0;
		while (*s == ' ')
			s++;
		if (*s != ' ' && *s != '\0')
			words++;
		while (*s != ' ' && *s != '\0')
		{
			if (*s == '"' || *s == '\'')
				s = skip_quotes(s, mini, *s, &num);
			s++;
		}
	}
	s++;
	return (words);
}

/*
** - Calculate the length of each word
** - In case a word is the text between quotes, the length is length - 2, quotes
** are not taken in this calculation
*/

int
	len_words(t_shell *mini, char *s)
{
	int	len;
	int	num;

	len = 0;
	num = 0;
	while (*s && *s != ' ')
	{
		if (*s == '"' || *s == '\'')
		{
			s = skip_quotes(s, mini, *s, &num);
			len += num;
		}
		len++;
		s++;
	}
	return (len);
}
