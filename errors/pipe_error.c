/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:12:20 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/16 18:15:53 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipis_error(int error, t_shell *mini)
{
	t_token	*aux;
	t_list	*token_aux;

	if (WEXITSTATUS(error) == 4 || WEXITSTATUS(error) == 13)
	{
		token_aux = mini->token_list;
		while (mini->fail_pipe)
		{
			token_aux = token_aux->next;
			mini->fail_pipe--;
		}
		aux = token_aux->content;
		ft_putstr_fd(aux->argv[0], 1);
		write(1, ": Command not found\n", 20);
		g_lsig = 127;
	}
	else if (WEXITSTATUS(error) == 3)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	end_process(int error, t_shell *mini)
{
	if (error != -1)
	{
		pipis_error(error, mini);
		if (g_lsig != -50 && g_lsig != -100)
			g_lsig = WEXITSTATUS(error);
		else if (g_lsig == -50)
			g_lsig = 130;
		else if (g_lsig == -100)
			g_lsig = 131;
	}
}
