/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 20:00:27 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/15 23:45:02 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	here_doc_in(char *doc)
{
	int	pid;
	int	fpipe[2];

	pipe(fpipe);
	pid = fork();
	if (!pid)
	{
		write(fpipe[1], doc, ft_strlen(doc));
		close(fpipe[0]);
		close(fpipe[1]);
		exit(0);
	}
	dup2(fpipe[0], STDIN_FILENO);
	close(fpipe[0]);
	close(fpipe[1]);
}

void	file_dup(t_token *aux)
{
	int	file_aux;

	if (aux->input == 2)
		here_doc_in(aux->db_inp);
	if (aux->input == 1)
	{
		file_aux = open(aux->file_in, O_RDONLY);
		dup2(file_aux, STDIN_FILENO);
		close(file_aux);
	}
	if (aux->output)
	{
		if (aux->output == 2)
			file_aux = open(aux->file_out, O_WRONLY | O_APPEND);
		else
			file_aux = open(aux->file_out, O_WRONLY);
		dup2(file_aux, STDOUT_FILENO);
		close(file_aux);
	}
}

static void	son_income(t_pipes *info, t_token *aux, t_shell *mini)
{
	aux->pid = fork();
	if (!aux->pid)
	{
		if (mini->num_pipes != info->i)
		{
			dup2(info->spipe, STDIN_FILENO);
			close(info->spipe);
		}
		close(info->fpipe[0]);
		if (info->i)
			dup2(info->fpipe[1], STDOUT_FILENO);
		close(info->fpipe[1]);
		file_dup(aux);
		if (!aux->argv[0])
			exit(0);
		builtin_check(aux, mini);
	}
	close(info->fpipe[1]);
}

static int	wait_em_all(t_shell *mini)
{
	int		i;
	int		out;
	int		sig;
	t_list	*aux;
	t_token	*tokoe;

	i = 0;
	out = 0;
	aux = mini->token_list;
	mini->fail_pipe = 0;
	while (i <= mini->num_pipes)
	{
		tokoe = aux->content;
		if (!waitpid(tokoe->pid, &sig, WNOHANG))
			continue ;
		if (!out && WEXITSTATUS(sig))
			out = sig;
		else if (!out)
			mini->fail_pipe++;
		if (aux->next)
			aux = aux->next;
		i++;
	}
	return (out);
}

int	patter(t_token *aux, t_list *lst_aux, t_shell *mini)
{
	t_pipes	info;

	ft_bzero(&info, sizeof(t_pipes));
	info.i = mini->num_pipes;
	pipe(info.fpipe);
	while (info.i > -1)
	{
		if (mini->num_pipes != info.i && info.i)
		{
			close(info.fpipe[1]);
			pipe(info.fpipe);
		}
		son_income(&info, aux, mini);
		if (mini->num_pipes != info.i)
			close(info.spipe);
		info.spipe = info.fpipe[0];
		if (info.i)
		{
			lst_aux = lst_aux->next;
			aux = lst_aux->content;
		}
		info.i--;
	}
	close(info.fpipe[1]);
	return (wait_em_all(mini));
}
