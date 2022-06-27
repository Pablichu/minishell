/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:39:15 by pcosta-j          #+#    #+#             */
/*   Updated: 2021/11/16 18:18:13 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** - im: start insertion mode
**	 - With this specification we can insert text, and it's writeen in terminal
** - ei: finish insertion mode
** - ft_memmove: in case I insert something between waht is written, move all
** the text one position to the right
*/

static void	read_printable(t_shell *mini)
{
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	write(1, mini->buff, mini->ret);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	ft_memmove(mini->buff_pos + 1, mini->buff_pos,
		ft_strlen(mini->buff_pos));
	*mini->buff_pos = mini->buff[0];
	mini->buff_pos++;
}

/*
** - Define what to do depending on what key you press
**	 - kl: cursor left key
**		- le: cursor left one character
**   - kr: cursor right key
**		- nd: cursor right one character
*/

static void	read_extension(t_shell *mini)
{
	if (mini->buff[0] == '\n')
	{
		if (!ft_strcmp(mini->buff_line, "\0"))
			write(1, "\n", 1);
		mini->ret = 6;
	}
	if (!ft_strcmp(mini->buff, tgetstr("kl", NULL)))
	{
		if (mini->buff_pos != mini->buff_line)
		{
			tputs(tgetstr("le", NULL), 1, ft_putchar);
			mini->buff_pos--;
		}
	}
	else if (!ft_strcmp(mini->buff, tgetstr("kr", NULL)))
	{
		if (*mini->buff_pos)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putchar);
			mini->buff_pos++;
		}
	}
}

/*
** - Define what to do depending on which key you press
**   - ku: cursor up key
**   - kd: cursor down key
**		- dl: delete one line
**		- LE = Cursor left %1 characters
** - With ths what I do is:
**	 - delete the line in terminal
**	 - write again the prompt
**	 - put in the line the corresponding historial line
*/

static void	read_updokey(t_shell *mini)
{
	if (!ft_strcmp(mini->buff, tgetstr("ku", NULL)) && !mini->delimit)
	{
		tputs(tgetstr("dl", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("LE", NULL), 0,
				24 + ft_strlen(mini->buff_line)), 1, ft_putchar);
		hist_up(mini->buff_line, &mini->buff_temp,
			&mini->updown, mini->historial_list);
		ft_putstr_fd("👊 minihostias👊 > ", 1);
		ft_putstr_fd(mini->buff_line, 1);
		mini->buff_pos = ft_strchr(mini->buff_line, '\0');
	}
	else if (!ft_strcmp(mini->buff, tgetstr("kd", NULL)) && !mini->delimit)
	{	
		tputs(tgetstr("dl", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("LE", NULL), 0,
				24 + ft_strlen(mini->buff_line)), 1, ft_putchar);
		hist_down(mini->buff_line, mini->buff_temp,
			&mini->updown, mini->historial_list);
		ft_putstr_fd("👊 minihostias👊 > ", 1);
		ft_putstr_fd(mini->buff_line, 1);
		mini->buff_pos = ft_strchr(mini->buff_line, '\0');
	}
}

/*
** - Define what to do depending on which key you press
** - 127: del key
**   - It depends where in the line I am (at the end or in the middle)
**		- le: cursor left one character
**		- dc: delete one character
** - 27 && *mini->buff_pos: press delete and I'm not at the end of the line
*/

static void	read_delete(t_shell *mini)
{
	if (*mini->buff == 127)
	{
		if (mini->buff_pos != mini->buff_line)
		{
			tputs(tgetstr("le", NULL), 1, ft_putchar);
			tputs(tgetstr("dc", NULL), 1, ft_putchar);
			if (*mini->buff_pos)
			{
				mini->buff_pos--;
				ft_memmove(mini->buff_pos, mini->buff_pos + 1,
					ft_strlen(mini->buff_pos));
			}
			else
			{	
				mini->buff_pos--;
				*mini->buff_pos = '\0';
			}
		}
	}	
	else if (mini->buff[0] == 27 && *mini->buff_pos)
	{
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		ft_memmove(mini->buff_pos, mini->buff_pos + 1,
			ft_strlen(mini->buff_pos));
	}
}

/*
** - This function takes you to the function you need dependind on pressed key
*/

int
	read_function(t_shell *mini)
{
	init_termcap(mini);
	mini->ret = read(STDIN_FILENO, &mini->buff, 5);
	if (mini->buff[0] == CTRL_D && !*mini->buff_line)
		mini->ret = 8;
	else if (mini->buff[0] == CTRL_D)
		mini->ret = 7;
	else if (mini->buff[0] == CTRL_C)
		mini->ret = 9;
	else if (ft_isprint(mini->buff[0]))
		read_printable(mini);
	else if (mini->buff[0] == '\n'
		|| !ft_strcmp(mini->buff, tgetstr("kl", NULL))
		|| !ft_strcmp(mini->buff, tgetstr("kr", NULL)))
		read_extension(mini);
	else if (!ft_strcmp(mini->buff, tgetstr("ku", NULL))
		|| !ft_strcmp(mini->buff, tgetstr("kd", NULL)))
		read_updokey(mini);
	else if (*mini->buff == 127 || (mini->buff[0] == 27 && *mini->buff_pos))
		read_delete(mini);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &mini->termios_backup);
	return (mini->ret);
}
