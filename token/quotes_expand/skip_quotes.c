/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:34:58 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/04 23:43:33 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** - This function checks if there is a quote in the string.
** It's supposed there is a previous quote --> you search closing quote
** - If there is a quote, it returns the position of this quote
** - If there is not a quote, returns an error --> quotes must be closed
*/

char
	*skip_quotes(char *str, t_shell *mini, char quote, int *len)
{
	char	*dq;

	if (quote == '"')
		mini->dquote = 1;
	if (quote == '\'')
		mini->quote = 1;
	str++;
	dq = ft_strchr(str, quote);
	if (!dq)
	{
		mini->error = 2;
		return (str);
	}
	*len = dq - str + 1;
	return (dq);
}

char
	*skip_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}
