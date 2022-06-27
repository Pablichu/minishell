/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:44:19 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/08/23 20:19:06 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	count_words(char const *s, char c)
{
	int	i;
	int	words;
	int	n;

	n = ft_strlen(s);
	i = 0;
	words = 0;
	while (i < n)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (words);
}

static int
	len_words(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char
	**free_malloc(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char
	**ft_split_cont(char const *s, char c, char **table)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] != '\0' && j < count_words(s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		table[j] = malloc(sizeof(char *) * (len_words(s, c, i) + 1));
		if (!table[j])
			return (free_malloc(table));
		while (s[i] != '\0' && s[i] != c)
			table[j][k++] = s[i++];
		table[j][k] = '\0';
		j++;
	}
	table[j] = NULL;
	return (table);
}

char
	**ft_split(char const *s, char c)
{
	char	**table;

	if (!s)
		return (NULL);
	table = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!table)
		return (NULL);
	return (ft_split_cont(s, c, table));
}
