/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_buil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:12:29 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/12/08 18:48:31 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	inside_quote(char *args, int *i, t_list *env_lst, int quote)
{
	while (quote)
	{
		if (is_bit_set(quote, 0x01)
			|| (is_bit_set(quote, 0x02) && args[*i] != '$'))
		{
			if ((args[*i] == '\'' && is_bit_set(quote, 0x01))
				|| (args[*i] == '\"' && is_bit_set(quote, 0x02)))
			{
				*i = *i + 1;
				return ;
			}
			write(STDOUT_FILENO, &args[*i], 1);
			*i = *i + 1;
		}
		else if (args[*i] == '$')
			print_dollar(args + *i, i, env_lst, quote);
	}
}

static void	especials(char *args, int *i, t_list *env_lst)
{
	int	quote;

	quote = 0;
	if (args[*i] == '\'')
		quote = set_bit(quote, 0x01);
	if (args[*i] == '\"')
		quote = set_bit(quote, 0x02);
	if (is_bit_set(quote, 0x01) || is_bit_set(quote, 0x02))
		*i = *i + 1;
	else
		print_dollar(args + *i, i, env_lst, 0);
	inside_quote(args, i, env_lst, quote);
}

static void	print_loop(char *args, int i, t_list *env_lst)
{
	while (args[i])
	{
		if (!ft_strchr("\'\" $", args[i]))
		{
			write(STDOUT_FILENO, &args[i], 1);
			i++;
		}
		else if (ft_strchr("\'\"$", args[i]))
			especials(args, &i, env_lst);
		while (args[i] == ' ' && args[i + 1] == ' ')
			i++;
		if (args[i] == ' ')
		{
			if (args[i + 1])
				write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
}

void	echo_buil(char *args, t_list *env_lst)
{
	int	i;

	args += bye_echo_problem(args);
	if (!*args)
		return ;
	i = 0;
	if (!ft_strncmp(args, "-n", 2) && (args[2] == ' ' || args[2] == '\0'))
		i = 2;
	while (args[i] == ' ')
		i++;
	print_loop(args, i, env_lst);
	if (!(!ft_strncmp(args, "-n", 2) && (args[2] == ' ' || args[2] == '\0')))
		write(STDOUT_FILENO, "\n", 1);
	exit(0);
}
