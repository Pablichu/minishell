/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:23:50 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/12/08 18:48:27 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_value(char *value, int mode)
{
	int	j;

	if (!value)
		return ;
	j = 0;
	while (value[j] == ' ' && !mode)
		j++;
	while (value[j])
	{
		if (value[j] != ' ' || mode)
			write(STDOUT_FILENO, &value[j], 1);
		else
		{
			while (value[j + 1] == ' ' && !mode)
				j++;
			write(STDOUT_FILENO, " ", 1);
		}
		j++;
	}
}

void	print_dollar(char *args, int *i, t_list *env_lst, int mode)
{
	char	*name;
	char	*value;
	int		j;

	j = 1;
	if (args[j] == '?')
	{
		ft_putnbr_fd(g_lsig, STDOUT_FILENO);
		*i = *i + 2;
		return ;
	}
	while (ft_isalnum(args[j]) || args[j] == '_')
		j++;
	if (j == 1)
	{
		write(1, "$", 1);
		*i = *i + 1;
		return ;
	}
	name = ft_substr(args, 1, j - 1);
	value = get_value(env_lst, name);
	free(name);
	*i = *i + j;
	print_value(value, mode);
}

int	bye_echo_problem(char *args)
{
	int		i;
	int		pass;
	char	*echo;

	echo = "echo";
	i = 0;
	pass = 0;
	while (*args == ' ')
	{
		pass++;
		args++;
	}
	while (i != 4 || *args != ' ')
	{
		if (*args == echo[i])
			i++;
		pass++;
		args++;
	}
	while (*args == ' ')
	{
		pass++;
		args++;
	}
	return (pass);
}
