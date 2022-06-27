/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:17:36 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/17 22:35:14 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	token(t_shell *mini)
{
	int	error;

	error = parse_pipe(mini);
	if (error)
	{
		if (mini->error == 2)
			printf("minishell: unclosed quotes are not treated\n");
		else
			printf("minishell: syntax error near unexpected token '|'\n");
		return (error);
	}
	error = parse_redir(mini, mini->token_list);
	if (error)
		return (error);
	return (0);
}

void	del_token_content(void *node)
{
	t_token	*tok;

	tok = node;
	if (tok->str)
		free(tok->str);
	if (tok->command)
		free(tok->command);
	if (tok->db_inp)
		free(tok->db_inp);
	if (tok->file_in)
		free(tok->file_in);
	if (tok->file_out)
		free(tok->file_out);
	if (tok->argv)
		ft_freee(tok->argv);
	tok->str = NULL;
	tok->command = NULL;
	tok->db_inp = NULL;
	tok->file_in = NULL;
	tok->file_out = NULL;
	tok->argv = NULL;
	free(tok);
}

/*
static void
	print_token(t_shell *mini, t_list *lst)
{
	t_token	*node;

	printf("\nAqui imprimo lista de parseo\n");
	while (lst)
	{
		node = lst->content;
		printf("Contenido: '%s'\n", node->str);
		if (node->command)
			printf("Comando: '%s'\n", node->command);
		if (node->file_in)
			printf("file input: -%s-\n", node->file_in);
		printf("flag input: %d\n", node->input);
		printf("fd input: %d\n", node->fd_in);
		printf("lo que hay en << es '%s'\n", node->db_inp);
		printf("fd output: %d\n", node->fd_out);
		if (node->file_out)
			printf("file output: -%s-\n", node->file_out);
		printf("flag output: %d\n", node->output);
		int j = count_words(mini, node->command);
		int k = 0;
		while (k < j)
		{
			if (node->argv[k])
				printf("palabra %d es :-%s-\n", k, node->argv[k]);
			k++;
		}
		printf("siguiente nodo\n\n");
		lst = lst->next;
	}
}
*/
