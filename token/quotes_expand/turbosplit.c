/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbosplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:44:19 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/16 18:03:50 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**turbo_cont(t_shell *mini, char *s, char **table, t_split *aux);
static char	**free_malloc(char **tab);
static void	init_values(t_split *aux, t_shell *mini, char *s);
static void	inside_values(t_split *aux, t_shell *mini, char *s);

char
	**turbosplit(t_shell *mini, char *s)
{
	char	**table;
	t_split	aux;

	if (!s)
		return (NULL);
	table = malloc(sizeof(char *) * (count_words(mini, s) + 1));
	if (!table)
		return (NULL);
	init_values(&aux, mini, s);
	return (turbo_cont(mini, s, table, &aux));
}

/*
** - Allocate space for number of words x length of each word in **argv
** - How to save this information:
**	 - The quotes are not stored
**	 - In case there are simple quotes and $, no expansion is done
**	 - In case there are double quotes or no quotes and $, expansion is done
*/

static char
	**turbo_cont(t_shell *mini, char *s, char **table, t_split *aux)
{
	while (*s != '\0' && aux->j < aux->words)
	{
		s = skip_spaces(s);
		inside_values(aux, mini, s);
		table[aux->j] = malloc(sizeof(char *) * (aux->lenw + 1));
		if (!table[aux->j])
			return (free_malloc(table));
		while ((*s != '\0') && (aux->k < aux->lenw))
		{
			if_dollar(*s, mini);
			table[aux->j][aux->k++] = *(s++);
		}
		table[aux->j++][aux->k] = '\0';
		if (mini->dollar || mini->quote || mini->dquote)
		{
			aux->temp = expand(table[aux->j - 1], mini);
			free(table[aux->j - 1]);
			table[aux->j - 1] = aux->temp;
		}
	}
	table[aux->j] = NULL;
	return (table);
}

static void
	init_values(t_split *aux, t_shell *mini, char *s)
{
	aux->j = 0;
	aux->words = count_words(mini, s);
	aux->temp = NULL;
}

static void
	inside_values(t_split *aux, t_shell *mini, char *s)
{
	aux->k = 0;
	aux->lenw = len_words(mini, s);
	mini->dollar = 0;
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
