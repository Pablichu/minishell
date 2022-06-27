/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_vble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:56:21 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/14 00:55:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env
	*new_vble(char *name, char *value)
{
	t_env	*envi;

	envi = malloc(sizeof(t_env));
	if (!envi)
		return (0);
	if (name)
		envi->name = ft_strdup(name);
	else
		envi->name = NULL;
	if (value)
		envi->value = ft_strdup(value);
	else
		envi->value = NULL;
	return (envi);
}

void
	del_env_content(void *node)
{
	t_env	*env;

	env = (t_env *)node;
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
	env->name = NULL;
	env->value = NULL;
	free(env);
}
