/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 00:44:52 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 23:54:27 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_redir(int c);
static int	join_inside(char *after, char *str, char **command, int c);

/*
** - Check if there are redirections in the string
**	 - If there are not, check if there is text after the file name (the file
**	 name has been saved in node in previous steps)
**	 - Make join of saved command with text after file name (arguments)
*/

char
	*join_command(t_token *node, char *str, int c)
{
	char	*aux;
	char	*after;
	char	*after2;
	int		not_c;

	not_c = get_redir(c);
	after = ft_strchr(str, c);
	after2 = ft_strchr(str, not_c);
	if ((after && after < after2) || (after && !after2))
		join_inside(after, str, &node->command, c);
	else if (after2)
		join_inside(after2, str, &node->command, not_c);
	else if (!after && !after2)
	{
		if (ft_strcmp(str, node->file_in) && ft_strcmp(str, node->file_out))
		{
			aux = ft_strjoin(node->command, str);
			free(node->command);
			node->command = aux;
		}
	}
	return (after);
}

static int
	join_inside(char *after, char *str, char **command, int c)
{
	char	*aux;

	*after = '\0';
	aux = ft_strjoin(*command, str);
	free(*command);
	*command = aux;
	*after = c;
	return (0);
}

static int
	get_redir(int c)
{
	int	not_c;

	not_c = 0;
	if (c == '<')
		not_c = '>';
	else if (c == '>')
		not_c = '<';
	return (not_c);
}

/*
** Auxiliar function for check_in & check_out in parse_redir
*/

void
	def_and_free(t_token *node, char *bk_str)
{
	char	*tempcommand;

	tempcommand = ft_strdup(bk_str);
	free(node->command);
	node->command = tempcommand;
}
