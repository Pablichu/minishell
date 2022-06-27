/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:56:48 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/15 21:57:07 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** - Input: list with the environment vbles and the name of a vble
** - If this vble exists, this function returns its value, else returns NULL
*/

char
	*get_value(t_list *env, char *name)
{
	t_env	*check;

	while (env)
	{
		check = env->content;
		if (!ft_strcmp(check->name, name))
			return (check->value);
		env = env->next;
	}
	return (NULL);
}

static inline void
	create_env(t_list **env, char *name, char *value, t_env *check)
{
	check = new_vble(name, value);
	ft_lstadd_back(env, ft_lstnew(check));
}

/*
** - This function can do two things depending if the environment vble
** exists or not:
**	- If exists, update its value with value
**	- If doesn't exist, create a new node in the list with given name and value
*/

void	set_value(t_list **env, char *name, char *value)
{
	t_env	*check;
	t_list	*current;

	if (!value)
		return ;
	current = *env;
	while (current)
	{
		check = current->content;
		if (check && check->name && !ft_strcmp(check->name, name))
		{
			if (value)
			{
				if (check->value)
					free(check->value);
				check->value = ft_strdup(value);
			}
			else if (!get_value(*env, name))
				check->value = NULL;
			return ;
		}
		current = current->next;
	}
	create_env(env, name, value, check);
	return ;
}
