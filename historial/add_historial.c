/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_historial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:43:03 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 20:36:24 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	del_hist_content(void *node)
{
	t_hist	*hist;

	hist = (t_hist *)node;
	if (hist->line)
		free(hist->line);
	if (hist->original)
		free(hist->original);
	free(hist);
}

t_hist
	*new_line(char *line)
{
	t_hist	*hist;

	hist = malloc(sizeof(t_hist));
	if (!hist)
		return (0);
	hist->line = ft_strdup(line);
	hist->original = ft_strdup(line);
	hist->pos = 0;
	return (hist);
}

/*
** - This function add the line written (this happens each time \n is pressed)
** - Call update node in case there are any change in the written line
*/

void
	add_historial(char *str, t_list **list_hist)
{
	t_hist	*hist;
	t_hist	*last_content;
	t_list	*last;

	if (str[0] == '\0')
		return ;
	hist = new_line(str);
	last = ft_lstlast(*list_hist);
	if (last)
	{
		last_content = last->content;
		hist->pos = last_content->pos + 1;
	}
	ft_lstadd_back(list_hist, ft_lstnew(hist));
	update_node(*list_hist);
}

void
	define_and_free(char *out, char *in)
{
	char	*temp1;

	if (out)
	{
		temp1 = ft_strdup(in);
		free(out);
		out = temp1;
	}
}

/*
static void print_historial(t_list *list)
{
	t_hist *hist;
	
	while (list)
	{
		hist = list->content;
		printf("   %d : %s\n", hist->pos, hist->line);
		list = list->next;
	}
}*/
