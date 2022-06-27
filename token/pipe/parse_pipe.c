/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:17:36 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/14 22:58:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_node(char *str);
static void		new_token(t_list **token_list, char *str);
static void		init_values(t_aux *aux, t_shell *mini);

/*
** - While there is no error and you have text in the written line
**	  - If there is a pipe
**		 - Increase the variable which counts pipes
**		 - Put the first position (where the pipe is) as null
**		 - If string is not empty, add a new node to the list with the written
**		 string
**		 - Advance one position to avoid the pipe I have treated
**	  - If there is double o simple quote
**		 - skip quotes with the corresponding function
** - If there is still something in the string after the last pipe, create a new
** node (it should be, a pipe can't be alone)
** - If number of nodes is different to the number of pipes + 1, it returns 3,
** which means no correct number of pipes
*/

int
	parse_pipe(t_shell *mini)
{
	t_aux	aux;

	init_values(&aux, mini);
	while (!mini->error && *aux.str)
	{
		if (*aux.str == '|')
		{
			mini->num_pipes++;
			*aux.str = '\0';
			if (ft_strlen(aux.begin_token))
				new_token(&mini->token_list, aux.begin_token);
			aux.begin_token = aux.str + 1;
		}
		if (*aux.str == '"' || *aux.str == '\'')
			aux.str = skip_quotes(aux.str, mini, *aux.str, &aux.count_skip);
		aux.str++;
	}
	if (ft_strlen(aux.begin_token))
		new_token(&mini->token_list, aux.begin_token);
	if (ft_lstsize(mini->token_list) != mini->num_pipes + 1)
		mini->error = 3;
	free(aux.backup_str);
	return (mini->error);
}

/*
** - Create the new node with the string str
** - Initialize the values of the file descriptors with a specific value
** for futures checkings
*/

static t_token
	*new_node(char *str)
{
	t_token	*token;

	token = calloc(1, sizeof(t_token));
	if (!token)
		return (0);
	token->str = ft_strdup(str);
	token->command = ft_strdup(str);
	token->db_inp = calloc(1, 1024);
	token->file_in = NULL;
	token->file_out = NULL;
	token->fd_in = -2;
	token->fd_out = -2;
	token->argv = NULL;
	return (token);
}

/*
** Add a new node
*/

static void
	new_token(t_list **token_list, char *str)
{
	t_token	*token;

	token = new_node(str);
	ft_lstadd_back(token_list, ft_lstnew(token));
}

/*
** - Function created to meet the norme.
** - Initialize values with an auxiliar structure
** - As I work with aux->str, store the position in aux->backup_str in order
** to be able to free ft_strdup
*/

static void
	init_values(t_aux *aux, t_shell *mini)
{
	ft_bzero(aux, sizeof(t_aux));
	aux->str = ft_strdup(mini->buff_line);
	aux->backup_str = aux->str;
	mini->error = 0;
	aux->begin_token = aux->str;
	mini->num_pipes = 0;
}
