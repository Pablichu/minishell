/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_dquote_aux_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:38:41 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 23:40:38 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*not_more_dollar(char *str, t_split *aux, t_shell *mini)
{
	check_vble_name(str, aux);
	if (!aux->j)
		aux->temp = str;
	else if (*aux->name)
		get_value_aux_what(aux);
	aux->vble = get_value(mini->env_list, str + 1);
	set_value_aux_what(aux);
	if (aux->vble)
	{
		if (aux->name)
			aux->temp = ft_strjoin(aux->vble, aux->name);
		else
			aux->temp = ft_strdup(aux->vble);
	}
	else
	{
		if (aux->name && aux->j)
			aux->temp = ft_strdup(aux->name);
	}
	set_values_aux_result(aux);
	free(aux->temp);
	return (aux->result);
}

void
	more_dollar(char *str, t_split *aux, t_shell *mini)
{	
	check_vble_name(str, aux);
	if (!aux->j)
		aux->temp = "$";
	else if (*aux->name)
		get_value_aux_what(aux);
	aux->vble = get_value(mini->env_list, str + 1);
	set_value_aux_what(aux);
	if (aux->vble)
	{
		if (aux->name && aux->j)
			aux->temp = ft_strjoin(aux->vble, aux->name);
		else if (!aux->name)
			aux->temp = ft_strdup(aux->vble);
	}
	else
	{
		if (aux->name && aux->j)
			aux->temp = ft_strdup(aux->name);
		else if (aux->name && !aux->j)
			aux->temp = ft_strjoin(aux->temp, aux->name);
	}
	set_values_aux_result(aux);
	free(aux->temp);
}
