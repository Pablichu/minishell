/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_dquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 22:16:22 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 23:53:10 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*init_values(t_shell *mini, t_aux *aux, char *str);
static void	set_values_aux_str(t_aux *aux, char *vble, char *temp);
static void	set_values_aux_after(t_aux *aux);

/*
** - aux->str is the possible text before the "" (this field store the previous
** value from one function to another)
**
** - str is the string which contains the text starting with "
** - Init_values:
**		- aux.after has value if there are $ in the text between quotes
**		- str = position after "
** - If there are not $ between ""
**		- if there is text in aux.str, join aux.str and text after "
**		- else aux.str is the text after "
** - If there are $ between ""
**		- Mark $ as 0
**		- aux.join2 is the text before $ (if there is)
**		- Mark again the position of $
**		- aux.join: check if there are more dollar in the text
*		- if there is text before $ (aux.join2), join this with aux.join
**		- aux.str (field used in all the functions)
**			- if there is text before "", aux.str = aux.str + text between ""
**			- if there is not text before "", aux.str = text between ""
** RETURN: texto after doble quote
*/

char
	*init_values_dquote(t_shell *mini, t_aux *aux, char *str)
{
	char	*temp;
	char	*temp1;

	temp = NULL;
	temp1 = NULL;
	str = init_values(mini, aux, str);
	if (!aux->after)
		set_values_aux_str(aux, aux->quote + 1, temp);
	else
	{
		set_values_aux_after(aux);
		temp1 = check_more_dollar(aux->after, mini);
		if (aux->join2)
		{
			aux->join = ft_strjoin(aux->join2, temp1);
			free(aux->join2);
			free(temp1);
		}
		set_values_aux_str(aux, aux->join, temp);
	}
	free(aux->join);
	return (str);
}

/*
** - aux.quote is the text starting with "
** - skip to the following " (closing doble quote)
** - str is the position of ", marks to 0
** - advance one position to avoid the "
** - aux.after has value if there are $ in the text between quotes
** RETURN: str = position after "
*/

static char
	*init_values(t_shell *mini, t_aux *aux, char *str)
{
	aux->quote = str;
	str = skip_quotes(str, mini, '"', &aux->len);
	*str = '\0';
	str++;
	aux->after = ft_strchr(aux->quote + 1, '$');
	return (str);
}

static void
	set_values_aux_str(t_aux *aux, char *vble, char *temp)
{
	if (aux->str)
	{
		temp = ft_strjoin(aux->str, vble);
		free(aux->str);
		aux->str = temp;
	}
	else
		aux->str = ft_strdup(vble);
}

static void
	set_values_aux_after(t_aux *aux)
{
	*aux->after = '\0';
	aux->join2 = ft_strdup(aux->quote + 1);
	*aux->after = '$';
}

/*
** - Check if there are more $ in the passed string
** - Every time it finds $, search for the corresponding environment vble
** - If there are several $, it concatenates text after/before/between and the
** corresponding vble in aux.result
** - RETURN aux.result (all the text concatenated and $ expanded)


static char
	*check_more_dollar(char *str, t_shell *mini)
{
	t_split	aux;

	ft_bzero(&aux, sizeof(t_split));
	while (str)
	{
		aux.aux = ft_strchr(str + 1, '$');
		aux.what = '\0';
		if (!aux.aux)
		{
			aux.j = 0;
			aux.name = str + 1;
			while (*aux.name && (*aux.name == '_' || ft_isalnum(*aux.name)))
			{
				aux.name++;
				aux.j++;
			}
			if (!aux.j)
				aux.temp = str;
			else if (*aux.name)
			{
				aux.what = *aux.name;
				*aux.name = '\0';
			}
			aux.vble = get_value(mini->env_list, str + 1);
			if (aux.what)
				*aux.name = aux.what;
			if (aux.vble)
			{
				if (aux.name)
					aux.temp = ft_strjoin(aux.vble, aux.name);
				else
					aux.temp = ft_strdup(aux.vble);
			}
			else
			{
				if (aux.name && aux.j)
					aux.temp = ft_strdup(aux.name);
			}
			if (aux.result)
			{
				char	*temp;
				temp = ft_strjoin(aux.result, aux.temp);
				free(aux.result);
				aux.result = temp;
			}
			else
				aux.result = ft_strdup(aux.temp);
			free(aux.temp);
			return (aux.result);
		}
		if (aux.aux)
		{
			*aux.aux = '\0';
			aux.j = 0;
			aux.name = str + 1;
			while (*aux.name && (*aux.name == '_' || ft_isalnum(*aux.name)))
			{
				aux.name++;
				aux.j++;
			}
			if (!aux.j)
				aux.temp = "$";
			else if (*aux.name)
			{
				aux.what = *aux.name;
				*aux.name = '\0';
			}
			aux.vble = get_value(mini->env_list, str + 1);
			if (aux.what)
				*aux.name = aux.what;
			if (aux.vble)
			{
				if (aux.name && aux.j)
					aux.temp = ft_strjoin(aux.vble, aux.name);
				else if (!aux.name)
					aux.temp = ft_strdup(aux.vble);
			}
			else
			{
				if (aux.name && aux.j)
					aux.temp = ft_strdup(aux.name);
				else if (aux.name && !aux.j)
					aux.temp = ft_strjoin(aux.temp, aux.name);
			}
			if (aux.result)
			{
				char	*temp;
				temp = ft_strjoin(aux.result, aux.temp);
				free(aux.result);
				aux.result = temp;
			}
			else
				aux.result = ft_strdup(aux.temp);
			free(aux.temp);
			*aux.aux = '$';
		}
		str = aux.aux;
	}
	return (aux.result);
}
*/

/*
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
