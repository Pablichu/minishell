/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 11:26:29 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/16 18:20:36 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(t_shell *mini, char **env);
static void	mini_loop(int decission, t_shell mini);
static void	del_and_free_content(t_shell *mini);

int	main(int argc, char **argv, char **env)
{
	t_shell	mini;

	(void)argc;
	(void)argv;
	init(&mini, env);
	mini_loop(0, mini);
	return (0);
}

static void	mini_loop(int decission, t_shell mini)
{
	while (1)
	{
		write(1, "👊 minihostias👊 > ", 24);
		decission = read_line(&mini);
		if (decission == 1 && !*mini.buff_line)
		{
			ft_putstr_fd("exit\n", 1);
			del_and_free_content(&mini);
			ft_freee(mini.mi_env);
			break ;
		}
		else if (decission == 2)
			ft_putstr_fd("\n", 1);
		else if (decission == 0 && mini.buff_line[0])
		{
			write(1, "\n", 1);
			add_historial(mini.buff_line, &mini.historial_list);
			decission = token(&mini);
			if (!decission)
				executer(&mini);
			ft_lstclear(&mini.token_list, del_token_content);
		}
		ft_bzero(&mini.buff, 5);
	}
}

/*
*	decission == 1 -> CTRL_D
*	decission == 2 -> CTRL_C
*	decission == 0 -> We got a line and going to execute
*	There was:
*	if (*mini.buff_line)
*			write(1, "\n", 1);
*	after the last else if
*	There was a continue in if (decission == 2)
*/

static void
	init(t_shell *mini, char **env)
{
	char	*aux;
	int		lvl;

	g_lsig = 0;
	ft_bzero(mini, sizeof(t_shell));
	mini->updown = -1;
	env_to_list(env, mini);
	aux = get_value(mini->env_list, "SHLVL");
	if (aux == NULL)
		set_value(&(mini)->env_list, "SHLVL", "1");
	else
	{
		lvl = ft_atoi(aux) + 1;
		aux = ft_itoa(lvl);
		set_value(&(mini)->env_list, "SHLVL", aux);
		free(aux);
	}
	mini->mi_env = list_to_env(mini->mi_env, mini->env_list);
}

static void
	del_and_free_content(t_shell *mini)
{
	ft_lstclear(&mini->token_list, del_token_content);
	ft_lstclear(&mini->historial_list, del_hist_content);
	ft_lstclear(&mini->env_list, del_env_content);
}
