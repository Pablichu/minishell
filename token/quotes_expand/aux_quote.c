/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:23:53 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 20:39:46 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	if_str_save_char_quote(t_aux *aux, char *str);
static void	if_previous_text_quote(t_aux *aux);

/*
** Auxiliar functions when *str = '
*/

char
	*init_values_quote(t_shell *mini, t_aux *aux, char *str)
{
	aux->redir = '\0';
	aux->medium = str;
	str = skip_quotes(str, mini, '\'', &aux->len);
	*str = '\0';
	str++;
	if_str_save_char_quote(aux, str);
	if_previous_text_quote(aux);
	*str = calc_char(str, aux->redir);
	return (str);
}

static void
	if_str_save_char_quote(t_aux *aux, char *str)
{
	if (*str)
	{
		aux->redir = *str;
		*str = '\0';
	}
}

static void
	if_previous_text_quote(t_aux *aux)
{
	char	*temp;

	if (aux->str)
	{
		temp = ft_strjoin(aux->str, aux->medium + 1);
		free(aux->str);
		aux->str = temp;
	}
	else
		aux->str = ft_strdup(aux->medium + 1);
}
