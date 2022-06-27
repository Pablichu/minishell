/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_dquote_aux_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 22:40:32 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 23:42:15 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** - Check if there are more $ in the passed string
** - Every time it finds $, search for the corresponding environment vble
** - If there are several $, it concatenates text after/before/between and the
** corresponding vble in aux.result
** - RETURN aux.result (all the text concatenated and $ expanded)
*/

char
	*check_more_dollar(char *str, t_shell *mini)
{
	t_split	aux;

	ft_bzero(&aux, sizeof(t_split));
	while (str)
	{
		aux.aux = ft_strchr(str + 1, '$');
		aux.what = '\0';
		if (!aux.aux)
			return (not_more_dollar(str, &aux, mini));
		if (aux.aux)
		{
			*aux.aux = '\0';
			more_dollar(str, &aux, mini);
			*aux.aux = '$';
		}
		str = aux.aux;
	}
	return (aux.result);
}

void
	check_vble_name(char *str, t_split *aux)
{
	aux->j = 0;
	aux->name = str + 1;
	while (*aux->name && (*aux->name == '_' || ft_isalnum(*aux->name)))
	{
		aux->name++;
		aux->j++;
	}
}

void
	set_values_aux_result(t_split *aux)
{
	char	*temp;

	temp = NULL;
	if (aux->result)
	{
		temp = ft_strjoin(aux->result, aux->temp);
		free(aux->result);
		aux->result = temp;
	}
	else
		aux->result = ft_strdup(aux->temp);
}

void
	get_value_aux_what(t_split *aux)
{
	aux->what = *aux->name;
	*aux->name = '\0';
}

void
	set_value_aux_what(t_split *aux)
{
	if (aux->what)
		*aux->name = aux->what;
}

/*
**	EXPLANATION OF ALL THIS FUNCTION TOGETHER
**	The function are in 2 files; aux_one and aux_two
**
** - While there is text
**	- Check if there are more dollar after the existing one
**	- Mark the char what as 0
**	1) If there is not more dollar
**	  - j = 0 (counter to know how much chars I advanced after $)
**	  - aux.name = position after $
**	  - while there is text after $ and (is alphabetic or numeric or _)
**		- advance in the string and count the characters advanced
**	  - If there is no char after $ which is part of the vble name
**		- aux.temp is the text with $
**	  - If there is text after $ which is part of the variable name
**		- store the first char in aux.what
**		- mark as 0 the first char which is not part of the vble name
**	  - aux.vble is the value of the env vble (if exists)
**	  - if there is a value in what, restore aux.name
**	  - If there is aux.vble
**		- if there is text after the vble name (aux.name)
**		  - aux.temp = aux.vble + aux.name
**		- if there is not text after the vble name
**		  - aux.temp = aux.vble
**	  - If there is not aux.vble (env vble)
**		- if there is text after $ and the counter is !=0 (advance in the text)
**		  - aux.temp = aux.name
**	  - If there is something stored in aux.result
**		  - aux.result = aux.result + temp
**	  - If there is nothing stored in aux.result
**		  - aux.result = aux.temp
**	- As there is not more $ neither text, this is the end in this case and
**	return aux.str
**
**	2) If there is more dollar
**	  - the position of $ is marked as 0
**	  - j = 0 (counter to know how much chars I advanced after $)
**	  - aux.name = position after $
**	  - while there is text after $ and (is alphabetic or numeric or _)
**		- advance in the string and count the characters advanced
**	  - If there is no char after $ which is part of the vble name
**		- aux.temp = $
**	  - If there is text after $ which is part of the variable name
**		- store the first char in aux.what
**		- mark as 0 the first char which is not part of the vble name
	  - aux.vble is the value of the env vble (if exists)
**	  - if there is a value in what, restore aux.name
**	  - If there is aux.vble
**		- if there is text after the vble name (aux.name)
**		  - aux.temp = aux.vble + aux.name
**		- if there is not text after the vble name
**		  - aux.temp = aux.vble
**	  - If there is not aux.vble (env vble)
**		- if there is text after $ and the counter is !=0 (advance in the text)
**		  - aux.temp = aux.name (text after env vble)
**		- if there is text after $ but counter = 0 (not part of the env name)
**		  - aux.temp = aux.temp + aux.name (what I already have + text after $)
**	  - If there is something stored in aux.result
**		  - aux.result = aux.result + temp
**	  - If there is nothing stored in aux.result
**		  - aux.result = aux.temp
** - Restore the value of aux.aux = $
** - str = the text just after this $, and start again to search more $ 
*/
