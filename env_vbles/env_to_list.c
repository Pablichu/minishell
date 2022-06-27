/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 10:23:59 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 21:06:47 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** - Turn ENV vble into a list
** - In this list we store in each node the name and the value of each
** environment variable
*/

void
	env_to_list(char **env, t_shell *mini)
{
	char	**chain;
	char	*med;
	t_env	*envi;
	int		i;

	if (!*env)
		return ;
	chain = env;
	i = 0;
	while (chain[i])
	{
		med = ft_strchr(chain[i], '=');
		*med = '\0';
		envi = new_vble(chain[i], med + 1);
		*med = '=';
		ft_lstadd_back(&mini->env_list, ft_lstnew(envi));
		i++;
	}
}

void
	print_env_list(t_list *env, const char *fn)
{
	t_env	*check;

	while (env)
	{
		check = env->content;
		if (!ft_strcmp(fn, "ft_export") && check->name)
			ft_putstr_fd("declare -x ", 1);
		if (!ft_strcmp(fn, "ft_export") || (check->value && check->value[0]))
			ft_putstr_fd(check->name, 1);
		if (check->value && check->value[0])
		{
			write(1, "=", 1);
			if (!ft_strcmp(fn, "ft_export"))
				write(1, "\"", 1);
			ft_putstr_fd(check->value, 1);
			if (!ft_strcmp(fn, "ft_export"))
				write(1, "\"", 1);
		}
		if ((!ft_strcmp(fn, "ft_export") && check->name)
			|| (check->value && check->value[0]))
			write(1, "\n", 1);
		env = env->next;
	}
}
