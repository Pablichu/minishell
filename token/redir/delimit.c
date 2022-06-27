/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 22:59:16 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/12/07 19:21:12 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_values(t_aux *aux, t_shell *mini);
static void	calc_values(t_aux *aux, t_shell *mini);
static char	*quit_quotes(char *limit, t_shell *mini);
static void	check_conditions(t_shell *mini, char *limit, t_aux *aux);

/*
** This function read what we write after double redirection
** - We do a backup of what there is in the line. We need it for future actions,
** and before to leave the function, mini->buff_line must recover what was in
** the line before to be in this function
** - Create a copy of the list in order not to miss the point to the first node
** - While there is << and the node in which I am it's not the corresponding
** to the double redir, or the node in which I am is one of the double redir but
** has something saved in the corresponding field, advance for searching the
** the node in which I have to store what is read from <<
** - Check of what is read with the corresponding delimiter and:
**		- If are equals, exit
**		- If press Ctrl-C, exit and nothing is stored
**		- If press Ctrl-D (with nothing written) or \n:
**			- Join what is in the field before with \n and with the read
**			- If I press \n, continue reading
**			- If I press Ctrl-D save and exit
*/

/*
** read_line = 0 -> \n
** read_line = 1 -> Ctrl+D and nothing in line
** read_line = 2 -> Ctrl+C
*/

// crear una función que obvie las comillas en limit y con eso estaría
void
	delimit(t_shell *mini, char *limit)
{
	t_aux	aux;

	init_values(&aux, mini);
	if (mini->quote || mini->dquote)
	{
		aux.temp = quit_quotes(limit, mini);
		limit = aux.temp;
	}
	check_conditions(mini, limit, &aux);
	write(1, "\n", 1);
	ft_memmove(mini->buff_line, aux.bkp_line, 1024);
}

static void
	init_values(t_aux *aux, t_shell *mini)
{
	mini->delimit = 1;
	ft_bzero(aux, sizeof(t_aux));
	ft_memmove(aux->bkp_line, mini->buff_line, 1024);
	aux->tok_list = mini->token_list;
	aux->node = aux->tok_list->content;
	while ((aux->tok_list && aux->node->input != 2)
		|| (aux->tok_list && aux->node->input == 2
			&& ft_strlen(aux->node->db_inp) > 0))
	{
		aux->tok_list = aux->tok_list->next;
		aux->node = aux->tok_list->content;
	}
	aux->node->fd_in = -1;
	write(1, "> ", 2);
}

static void
	calc_values(t_aux *aux, t_shell *mini)
{
	aux->join = ft_strjoin(mini->buff_line, "\n");
	if (aux->num == 1)
		return ;
	aux->join2 = ft_strjoin(aux->node->db_inp, aux->join);
	free(aux->join);
	free(aux->node->db_inp);
	aux->node->db_inp = aux->join2;
}

static char
	*quit_quotes(char *limit, t_shell *mini)
{
	char	*temp;
	int		i;

	i = 0;
	temp = ft_calloc(sizeof(char) * ft_strlen(limit), 1);
	while (*limit)
	{
		if (mini->dquote && *limit == '"')
		{
			limit++;
			limit = advance_limit(limit, &i, temp);
		}
		else if (mini->quote && *limit == '\'')
			limit++;
		limit = advance_limit(limit, &i, temp);
	}
	return (temp);
}

static void
	check_conditions(t_shell *mini, char *limit, t_aux *aux)
{
	while (ft_strcmp(mini->buff_line, limit))
	{
		aux->num = read_line(mini);
		if (!ft_strcmp(mini->buff_line, limit))
		{
			if (mini->quote || mini->dquote)
				free(limit);
			break ;
		}
		if (aux->num == 2)
		{
			mini->error = 7;
			break ;
		}
		if (aux->num == 0 || aux->num == 1)
		{
			calc_values(aux, mini);
			if (aux->num == 0)
				write(1, "\n> ", 3);
			else
				break ;
		}
	}
}
