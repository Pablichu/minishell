/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:17:36 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/17 22:38:57 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_in(t_shell *mini, t_token *node, char *str, char *bk_str);
static char	*check_out(t_shell *mini, t_token *node, char *str, char *bk_str);
static void	init_values(t_token *node, t_aux *aux, t_shell *mini);
static void	free_and_define(t_aux *aux);

/*
** - While there are nodes in the list (list where the tokens are stored)
**	 - While there is no error and we are not at the end of the string
**		- If there is < call the corresponding function
**		- If there is > call the corresponding function
**		- If there is " ó ' call the function that ignores text between quotes
*/

int
	parse_redir(t_shell *mini, t_list *lst)
{
	t_token	*node;
	t_aux	aux;

	ft_bzero(&aux, sizeof(t_aux));
	while (lst)
	{
		node = lst->content;
		init_values(node, &aux, mini);
		while (!mini->error && *aux.str)
		{
			aux.temp = NULL;
			if (*aux.str == '<')
				aux.temp = check_in(mini, node, aux.str, aux.backup_str);
			else if (*aux.str == '>')
				aux.temp = check_out(mini, node, aux.str, aux.backup_str);
			else if (*aux.str == '"' || *aux.str == '\'')
				aux.str = skip_quotes(aux.str, mini, *aux.str, &aux.len);
			free_and_define(&aux);
			aux.str++;
		}
		node->argv = turbosplit(mini, node->command);
		lst = lst->next;
		free(aux.backup_str);
	}
	return (mini->error);
}

static void
	init_values(t_token *node, t_aux *aux, t_shell *mini)
{
	aux->str = ft_strdup(node->str);
	aux->backup_str = aux->str;
	mini->error = 0;
}

static void
	free_and_define(t_aux *aux)
{
	if (aux->temp)
	{
		free(aux->backup_str);
		aux->str = aux->temp;
		aux->backup_str = aux->str;
	}
}

/*
** - Check redir <
** - Advance one position
**	  - If there is not file (value initialized for me) save the command
**	  - If there is another < mark the redir flag as 2
** - Save file name
** - Call the functions that treat:
	  - File name
	  - Possible commands
	  - Possible flags/options after commands
*/

static char
	*check_in(t_shell *mini, t_token *node, char *str, char *bk_str)
{	
	*str = '\0';
	str++;
	if (node->fd_in == -2 && node->fd_out == -2)
		def_and_free(node, bk_str);
	if (*str == '<')
	{
		node->input = 2;
		str++;
		if (*str == '<')
		{
			mini->error = 1;
			write(1, "minishell: syntax error near unexpected token `<'\n", 51);
			return (str);
		}
	}
	else
		node->input = 1;
	str = skip_spaces(str);
	node->file_in = ft_strdup(str);
	str = get_file(mini, node, &node->file_in, 'i');
	if ((node->fd_in != -2 || node->input == 2) && !node->not_arg)
		join_command(node, str, '<');
	return (str);
}

/*
** - When call join_command function?
** It's necessary:
**		- file has been opened previously (fd != 0)
**		or be double redirection (only for <<)
**		- there must be argument to join with the command
*/

/*
** Same as previous function but with >
*/

static char
	*check_out(t_shell *mini, t_token *node, char *str, char *bk_str)
{
	*str = '\0';
	str++;
	if (node->fd_out == -2 && node->fd_in == -2)
		def_and_free(node, bk_str);
	if (*str == '>')
	{
		node->output = 2;
		str++;
		if (*str == '>')
		{
			mini->error = 1;
			write(1, "minishell: syntax error near unexpected token `>'\n", 51);
			return (str);
		}
	}
	else
		node->output = 1;
	str = skip_spaces(str);
	node->file_out = ft_strdup(str);
	str = get_file(mini, node, &node->file_out, 'o');
	if (node->fd_out != -2 && !node->not_arg)
		join_command(node, str, '>');
	return (str);
}
