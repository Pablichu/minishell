/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:35:12 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/14 01:39:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** - Init termcaps what all the specifications we need
** - Save the information in termios_backup in order to return to default values
** - Change the specifications in our terminal with termios_new
** - ks: recognize the keys pressed in each terminal I am. If I don't do this,
** it would be necessary to introduce the code of each key, what be recognized
** only in the terminal in which I am
*/

void
	init_termcap(t_shell *mini)
{
	mini->term_name = getenv("TERM");
	tgetent(NULL, mini->term_name);
	ft_bzero(&mini->termios_new, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, &mini->termios_backup);
	mini->termios_new = mini->termios_backup;
	mini->termios_new.c_lflag &= ~(ICANON | ECHO);
	mini->termios_new.c_cc[VMIN] = 1;
	mini->termios_new.c_cc[VINTR] = 0;
	mini->termios_new.c_cc[VSUSP] = 0;
	mini->termios_new.c_cc[VSTOP] = 0;
	mini->termios_new.c_cc[VQUIT] = 0;
	mini->termios_new.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &mini->termios_new);
	tputs(tgetstr("ks", NULL), 1, ft_putchar);
}

/*
** - Read each line and act depending of what you press
**	 - mini.ret = 6 --> \n is pressed
**	 - mini.ret = 8 --> CTRL+D is pressed and there is no line
**	 - mini.ret = 9 --> CTRL+C is pressed
*/

int
	read_line(t_shell *mini)
{
	ft_bzero(mini->buff_line, 1024);
	mini->updown = -1;
	mini->buff_pos = mini->buff_line;
	*mini->buff_pos = '\0';
	while (read_function(mini) > 0)
	{
		if (mini->ret == 6)
			return (0);
		else if (mini->ret == 8)
			return (1);
		else if (mini->ret == 9)
			return (2);
	}
	ft_putnbr_fd(read_function(mini), 1);
	if (*(mini)->buff_temp)
		free(mini->buff_temp);
	return (3);
}
