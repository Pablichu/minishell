/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:00:57 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 23:53:24 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*if_previous_text(t_aux *aux, char *str);

/*
** - You are in this funciont if there is a $ with " or without quotes; the
** important thing is there must be a $ when you are here
**
**	- aux.before stores text before $, in case there is text
**	- Advance one position in aux.dollar to avoid $
**	- It could be text after $ (here the text after $ is if there is an space
**	and then more text, not concatenated with $ as an only word)
**	- aux.after stores text after $ (with a space between)
**	- aux.medium checks if there is more than one $ all together and search for
**	the corresponding environment vble
**	- if exists before, join before + medium
**	- if exists after, join medium + before
*/

char
	*expand(char *str, t_shell *mini)
{
	t_aux	aux;

	ft_bzero(&aux, sizeof(t_aux));
	while (*str)
	{
		if (*str && *str == '$')
			str = init_values_dollar(mini, &aux, str);
		if (*str && *str == '"')
			str = init_values_dquote(mini, &aux, str);
		if (*str && *str == '\'')
			str = init_values_quote(mini, &aux, str);
		if (*str && *str != '\'' && *str != '$' && *str != '"')
			str = if_previous_text(&aux, str);
		if (!*str)
			break ;
	}
	mini->dollar = 0;
	mini->quote = 0;
	mini->dquote = 0;
	return (aux.str);
}

static char
	*if_previous_text(t_aux *aux, char *str)
{
	char	*temp;

	aux->maybe[0] = *str;
	aux->maybe[1] = '\0';
	if (aux->str)
	{
		temp = ft_strjoin(aux->str, aux->maybe);
		free(aux->str);
		aux->str = temp;
	}
	else
		aux->str = ft_strdup(aux->maybe);
	str++;
	return (str);
}

char
	calc_char(char *dest, char source)
{
	if (source)
		*dest = source;
	return (*dest);
}
