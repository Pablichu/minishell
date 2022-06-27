/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exist_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 00:35:13 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/12/07 19:17:25 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exist_file_in(t_shell *mini, char *name, int *fd, int flag);
static int	exist_file_out(t_shell *mini, char *name, int *fd, int flag);

void
	exist_file(t_shell *mini, char c, t_token *node)
{
	char	*tempfile;

	tempfile = NULL;
	if (c == 'i')
	{
		if (node->input == 1)
			tempfile = expand(node->file_in, mini);
		else if (node->input == 2)
			tempfile = ft_strdup(node->file_in);
		free(node->file_in);
		node->file_in = tempfile;
		exist_file_in(mini, node->file_in, &node->fd_in, node->input);
		mini->delimit = 0;
	}
	else
	{
		tempfile = expand(node->file_out, mini);
		free(node->file_out);
		node->file_out = tempfile;
		exist_file_out(mini, node->file_out, &node->fd_out, node->output);
	}
}

static int
	exist_file_out(t_shell *mini, char *name, int *fd, int flag)
{	
	if (!name)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		mini->error = 1;
		return (3);
	}
	if (flag == 1)
		*fd = open(name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		*fd = open(name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*fd == -1)
	{
		perror(name);
		mini->error = 1;
	}
	close(*fd);
	return (0);
}

static int
	exist_file_in(t_shell *mini, char *name, int *fd, int flag)
{
	char	*endfile;

	if (!name)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		mini->error = 1;
		return (5);
	}
	endfile = ft_strtrim(name, " ");
	if (flag == 1)
	{
		*fd = open(name, O_RDONLY);
		if (*fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", endfile);
			mini->error = 1;
			free(endfile);
			return (4);
		}
		close(*fd);
	}
	else
		delimit(mini, endfile);
	free(endfile);
	return (0);
}

/*
** Auxiliar function for get_file
**
** - If there are redirections, take only text before redirection, and
** let str as it is for advancing in it
** - If there are not redirections, as there are not spaces means there is
** nothing more, so str only contains the file
*/

void
	not_args_maybe_redir(t_aux *aux, char **file, int *not_arg)
{
	char	*temp;

	if (aux->redir_in)
	{
		aux->temp = ft_strchr(aux->str, aux->redir);
		*aux->temp = '\0';
		temp = ft_strdup(aux->str);
		*aux->temp = aux->redir;
		free(aux->aux);
		aux->aux = ft_strdup(aux->str);
		free(*file);
		*file = temp;
	}
	else
	{
		temp = ft_strdup(aux->str);
		aux->aux = ft_strdup(aux->str);
		free(*file);
		*file = temp;
	}
	*not_arg = 1;
}

/*
** Auxiliar function for delimit
*/
char
	*advance_limit(char *limit, int *i, char *temp)
{
	if (*limit)
	{
		temp[*i] = *limit;
		(*i)++;
		limit++;
	}
	return (limit);
}
