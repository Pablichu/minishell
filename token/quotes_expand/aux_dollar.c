/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:23:53 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 20:40:08 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	if_str_save_char_dollar(t_aux *aux, char *str);
static void	if_name_and_or_before(t_shell *mini, t_aux *aux);
static void	if_previous_text_dollar(t_aux *aux);

/* 
** Auxiliar functions when *str = $
*/

char
	*init_values_dollar(t_shell *mini, t_aux *aux, char *str)
{
	aux->j = 0;
	aux->num = 0;
	aux->aux = str;
	aux->what = '\0';
	*str = '\0';
	aux->before = aux->aux;
	str++;
	aux->dollar = str;
	while (*str && (*str == '_' || ft_isalnum(*str)))
	{
		aux->j++;
		str++;
	}
	if (!aux->j)
	{
		aux->bkp = ft_strjoin(aux->before, "$");
		aux->before = aux->bkp;
	}
	if_str_save_char_dollar(aux, str);
	if_name_and_or_before(mini, aux);
	if_previous_text_dollar(aux);
	*str = calc_char(str, aux->what);
	free(aux->temp);
	return (str);
}

static void
	if_str_save_char_dollar(t_aux *aux, char *str)
{
	if (*str)
	{
		aux->what = *str;
		*str = '\0';
	}
}

static void
	if_name_and_or_before(t_shell *mini, t_aux *aux)
{
	aux->name = get_value(mini->env_list, aux->dollar);
	if (aux->name)
	{
		if (aux->before)
			aux->temp = ft_strjoin (aux->before, aux->name);
		else
			aux->temp = ft_strdup(aux->name);
	}
	else
		if (aux->before)
			aux->temp = ft_strdup(aux->before);
}

static void
	if_previous_text_dollar(t_aux *aux)
{
	char	*temp;

	if (aux->str)
	{
		temp = ft_strjoin(aux->str, aux->temp);
		free(aux->str);
		aux->str = temp;
	}
	else
		aux->str = ft_strdup(aux->temp);
	if (!aux->j)
		free(aux->before);
}

void
	if_dollar(char c, t_shell *mini)
{
	if (c == '$')
		mini->dollar = 1;
}
