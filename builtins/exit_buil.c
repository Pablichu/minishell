/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_buil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:09:00 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/16 18:13:49 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	good_or_not(int error, char *argv)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (!error)
		return (ft_atoi(argv));
	else
	{
		ft_putstr_fd(argv, STDOUT_FILENO);
		write(STDOUT_FILENO, ": numeric argument required\n", 29);
		return (1);
	}	
}

void	exit_buil(int pipes, char **argv)
{
	int	i;
	int	error;

	error = 0;
	if (argv[1] && !pipes)
	{
		if (argv[2])
		{
			write(STDOUT_FILENO, "exit: too many arguments\n", 25);
			exit(1);
		}
		i = 0;
		if ((argv[1][0] == '+' || argv[1][0] == '-') && !ft_isdigit(argv[1][1]))
			error = 1;
		else if (argv[1][0] == '+' || argv[1][0] == '-')
			i++;
		while (argv[1][i] && !error)
		{
			if (!ft_isdigit(argv[1][i]))
				error = 1;
			i++;
		}
		error = good_or_not(error, argv[1]);
	}
	exit(error);
}
