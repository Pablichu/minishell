/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:20:39 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/15 20:52:29 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_son(t_token *aux, t_shell *mini)
{
	if (!ft_strncmp(aux->argv[0], "export", 7) && aux->argv[1] != 0)
	{
		export_buil(aux->argv + 1, &(mini)->env_list, mini->mi_env, 0);
		ft_freee(mini->mi_env);
		mini->mi_env = list_to_env(mini->mi_env, mini->env_list);
		return (-1);
	}
	else if (!ft_strncmp(aux->argv[0], "unset", 6))
	{
		if (aux->argv[1])
			mini->mi_env = unset_buil(aux->argv + 1, mini->mi_env,
					mini->env_list, 0);
		g_lsig = 0;
		return (-1);
	}
	else if (!ft_strncmp(aux->argv[0], "cd", 3))
	{
		cd_buil(aux->argv[1], mini->env_list, 0);
		ft_freee(mini->mi_env);
		mini->mi_env = list_to_env(mini->mi_env, mini->env_list);
		return (-1);
	}
	else if (!ft_strncmp(aux->argv[0], "exit", 5))
		exit_buil(mini->num_pipes, aux->argv);
	return (0);
}

int	one_command(t_token *aux, t_shell *mini)
{
	int		pid;

	if (!aux->argv[0])
		return (0);
	if (no_son(aux, mini) == -1)
		return (-1);
	pid = fork();
	if (!pid)
	{
		file_dup(aux);
		builtin_check(aux, mini);
	}
	wait(&pid);
	mini->fail_pipe = 0;
	return (pid);
}
