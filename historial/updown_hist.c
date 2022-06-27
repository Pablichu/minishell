/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updown_hist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 18:55:38 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/15 20:34:16 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_value_and_free(char *buff_temp, char *buff_line);

/*
** - buff_line is what I have written in the prompt, and it's not mandatory to
** be in historial, because it could be possible that \n have not been pressed
** - To check with printf:
** dprintf(2, "\nup num_nodos:%d updown:%d pos:%d buff_line:%s buff_temp:%s\n",
** num_nodos, *updown, pos, buff_line, *buff_temp);
*/

/*
** - This function is executed when I pressed key up
** - Check number of nodes
** - If there is no nodes or I pressed key up more times of number of nodes
**		- Return what there is in the line at this moment
** - If I'm in the initial position, that is, the last position to show, save in
** the temporal what there is in that moment in the line (because it's possible
** to write in the line without press \n, and I need it for when I go down in
** historial when press key down)
** - If not in the initial position, update historial
** - Increase by one unit each time I press the key
** - While there is historial
**		- Go to the node in the position I am (nodes - times I pressed the key)
*/

char
	*hist_up(char *buff_line, char **buff_temp, int *updown, t_list *hist)
{
	t_hist	*line;
	int		num_nodos;
	int		pos;

	num_nodos = ft_lstsize(hist) - 1;
	if (num_nodos < 0 || *updown >= num_nodos)
		return (buff_line);
	if (*updown == -1)
		define_and_free(*buff_temp, buff_line);
	else
		update_hist(buff_line, num_nodos - *updown, hist);
	(*updown)++;
	pos = num_nodos - *updown;
	while (hist)
	{
		line = hist->content;
		if (line->pos == pos)
			break ;
		hist = hist->next;
	}
	ft_bzero(buff_line, sizeof(char) * 1024);
	ft_memmove(buff_line, line->line, ft_strlen(line->line));
	return (buff_line);
}

/*
** - This function is executed when key down is pressed
** - Check number of nodes
** - If there is no nodes or I pressed key down more times of number of nodes
**		- Return what there is in the line at this moment
** - Update historial: if something is added in this line for not missing it
** - Each time I pressed key down, decrease in one unit the counter
** - If I'm in the last line to show, update what I see with the value in the
** temporal, it could be nothing, or if I write something (without press \n),
** show it (what it's in the temporal nothing happens till \n is pressed)
** - If it's possible to come back in the historial:
**	- While there is historial
**		- Check which is the position I have to access (nodes - times I pressed
**		key down)
**		- Store in buff_line the content of this position
** - Return buff_line
*/

char
	*hist_down(char *buff_line, char *buff_temp, int *updown, t_list *hist)
{
	t_hist	*line;
	int		num_nodos;

	num_nodos = ft_lstsize(hist) - 1;
	if (num_nodos < 0 || *updown < 0)
		return (buff_line);
	update_hist(buff_line, num_nodos - *updown, hist);
	ft_bzero(buff_line, sizeof(char) * 1024);
	if (--(*updown) == -1)
		restore_value_and_free(buff_temp, buff_line);
	else
	{
		while (hist)
		{
			line = hist->content;
			if (line->pos == num_nodos - *updown)
				break ;
			hist = hist->next;
		}
		ft_memmove(buff_line, line->line, ft_strlen(line->line));
	}
	return (buff_line);
}

/*
** - While there are nodes in the list, that is, while there is historial:
**		- Go to the node content
**		- Check if the position I'm searching for is in the list
**		- In this position store the content of the line at this moment
*/

void
	*update_hist(char *buff_line, int pos, t_list *historial)
{
	t_hist	*line;

	while (historial)
	{
		line = historial->content;
		if (line->pos == pos)
		{	
			free(line->line);
			line->line = ft_strdup(buff_line);
		}	
		historial = historial->next;
	}
	return (0);
}

/*
** How works historial:
** - Introduce several orders in the command line: 1, 2, 3, 4
** - My historial has 4 nodes. If I modify one of them, and move for the
** historial without press \n, this modification keeps itself in the node in
** which you are (update_hist function
** - If you press \n in this line, what happens is that a new node is added to
** the list, and the modified node keeps as it was.
** - This case is what this function solved
*/

void
	update_node(t_list *list)
{
	t_hist	*last;
	t_hist	*old;
	char	*temp;

	if (list)
	{
		last = ft_lstlast(list)->content;
		while (list->next)
		{
			old = list->content;
			if (!ft_strcmp(last->line, old->line))
			{
				temp = ft_strdup(old->original);
				free(old->line);
				old->line = temp;
			}
			list = list->next;
		}
	}
}

/*
** Example: 
** - My historial is: 1, 2, 3, 4 (I have 4 nodes)
** - Modify second node, and add 2222 -> NOT PRESS \n
** - When I move inside historial, what appears is 1, 2222, 3, 4
** - Go to the line where 2222 is, and press \n
** - Now I have 5 nodes, which are 1, 2, 3, 4, 2222
*/

static void
	restore_value_and_free(char *buff_temp, char *buff_line)
{
	if (buff_temp)
	{
		ft_memmove(buff_line, buff_temp, ft_strlen(buff_temp));
		free(buff_temp);
	}
}
