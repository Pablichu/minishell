/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:17:36 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 23:54:16 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_values(t_token *node, t_aux *aux, char *file);
static void	get_before_redir(t_aux *aux, char *file);
static void	get_file_and_go_to_args(t_aux *aux, char **file);
static void	go_end_quotes(t_aux *aux, t_shell *mini);

/*
** - Depending of the redirection, save the file nmae in input or output
** - Search if there is something after file name
**		- If there is space means there is argument, save only file name
**		- If there is not space and there is a redirecction, save only file name
** - If there is nothing after file name, finish
**
** Steps:
** - Check if there are another redir to take only what there is before redir
** - If there is temp --> there is redir. Take only text before redir
** - If there is no temp --> no more redir, but there is fiel with or without
** arguments for the command
** - Advance in aux.before while there are not spaces
** I'm here for 2 reasons:
**		- There is space in before
**		- I'm at the end of the string there is nothing more (no arguments)
** - If there is aux.before: there is space --> there is arguments
** - If there is not aux.before: there is not spaces -->no arguments, but maybe
** there are redir after
*/

char
	*get_file(t_shell *mini, t_token *node, char **file, int c)
{
	t_aux	aux;

	init_values(node, &aux, *file);
	while (*aux.temp && *aux.temp != '<' && *aux.temp != '>')
		aux.temp++;
	if (aux.temp)
		get_before_redir(&aux, *file);
	while (*aux.before && *aux.before != ' ')
	{
		if (*aux.before && (*aux.before == '"' || *aux.before == '\''))
			go_end_quotes(&aux, mini);
		aux.before++;
		aux.len++;
	}
	if (*aux.before)
		get_file_and_go_to_args(&aux, file);
	else
		not_args_maybe_redir(&aux, file, &node->not_arg);
	exist_file(mini, c, node);
	free(aux.backup_str);
	return (aux.aux);
}

static void
	init_values(t_token *node, t_aux *aux, char *file)
{
	node->not_arg = 0;
	aux->temp = file;
	aux->before = file;
	aux->str = file;
	aux->quote = file;
	aux->len = 0;
	aux->num = 0;
	aux->redir_in = 0;
	aux->aux = NULL;
}

static void
	get_before_redir(t_aux *aux, char *file)
{
	aux->redir = *aux->temp;
	*aux->temp = '\0';
	aux->before = ft_strdup(file);
	aux->backup_str = aux->before;
	*aux->temp = aux->redir;
	aux->redir_in = 1;
}

static void
	get_file_and_go_to_args(t_aux *aux, char **file)
{
	char	*temp;

	aux->what = *(aux->str + aux->len);
	*(aux->str + aux->len) = '\0';
	temp = ft_strdup(aux->str);
	*(aux->str + aux->len) = aux->what;
	aux->str += aux->len;
	free(aux->aux);
	aux->aux = ft_strdup(aux->str);
	free(*file);
	*file = temp;
}

static void
	go_end_quotes(t_aux *aux, t_shell *mini)
{
	aux->what = *aux->before;
	aux->quote = skip_quotes(aux->before, mini, aux->what, &aux->count_skip);
	aux->num = ft_strlen(aux->before) - ft_strlen(aux->quote);
	aux->len += aux->num;
	aux->before = aux->quote;
}
