/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 11:14:48 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/14 01:03:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** - Turn the list in which env vbles are stored into an array
** - The purpose is use this array as our own env
*/

char	**list_to_env(char **mi_env, t_list *env)
{
	t_env	*check;
	t_aux	aux;

	ft_bzero(&aux, sizeof(t_aux));
	aux.num = ft_lstsize(env);
	mi_env = malloc(sizeof(char *) * (aux.num + 1));
	ft_bzero(mi_env, sizeof(char *) * (aux.num + 1));
	if (!mi_env)
		return (NULL);
	aux.j = 0;
	while (env)
	{
		check = env->content;
		aux.var1 = ft_strdup(check->name);
		aux.var2 = ft_strjoin(aux.var1, "=");
		mi_env[aux.j] = ft_strjoin(aux.var2, check->value);
		free(aux.var2);
		free(aux.var1);
		env = env->next;
		aux.j++;
	}
	mi_env[aux.j] = NULL;
	return (mi_env);
}

/*
** static void
** 	print_env_array(char **env)
** {
** 	char	**str;
** 	int		i;
**
** 	str = env;
** 	i = 0;
** 	while (str[i])
** 	{
** 		ft_putstr_fd(str[i], 1);
** 		write(1, "\n", 1);
** 		i++;
** 	}
** 	return ;
** }
*/
