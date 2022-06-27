/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_buil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:59:47 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/03 20:20:24 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(void *content)
{
	t_env	*env;

	env = content;
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
}

static void	unset_value(t_list **env, char *name, t_list *current)
{
	t_env	*check;
	t_list	*back;

	check = current->content;
	if (check && check->name && !ft_strcmp(check->name, name))
	{
		*env = (*env)->next;
		ft_lstdelone(current, del_env);
		return ;
	}
	back = current;
	current = current->next;
	while (current)
	{
		check = current->content;
		if (check && check->name && !ft_strcmp(check->name, name))
		{
			back->next = current->next;
			ft_lstdelone(current, del_env);
			return ;
		}
		back = current;
		current = current->next;
	}
	return ;
}

char	**unset_buil(char **commands, char **mi_env, t_list *lst_env, int mode)
{
	int		j;

	if (*commands && !mode)
	{
		if (!lst_env)
			return (mi_env);
		j = 0;
		while (commands[j])
		{
			unset_value(&lst_env, commands[j], lst_env);
			j++;
		}
		ft_freee(mi_env);
		mi_env = list_to_env(mi_env, lst_env);
		return (mi_env);
	}
	exit (0);
}
