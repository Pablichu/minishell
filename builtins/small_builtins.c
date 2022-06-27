/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:40:53 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/16 18:09:47 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_buil(char *command, t_list *env_lst, int mode)
{
	char	dir[PATH_MAX];

	getcwd(dir, sizeof(dir));
	if (chdir(command))
	{
		if (mode)
			return (5);
		perror("cd");
		g_lsig = 1;
		return (1);
	}
	else
	{
		set_value(&env_lst, "OLDPWD", dir);
		getcwd(dir, sizeof(dir));
		set_value(&env_lst, "PWD", dir);
	}
	return (0);
}

void	env_buil(char **env)
{
	int	i;

	i = 0;
	if (*env)
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '='))
			{
				ft_putstr_fd(env[i], STDOUT_FILENO);
				write(STDOUT_FILENO, "\n", 1);
			}
			i++;
		}
	}
	else
		write(STDOUT_FILENO, "\n", 1);
	exit(0);
}

void	pwd_buil(void)
{
	char	dir[PATH_MAX];

	getcwd(dir, sizeof(dir));
	ft_putstr_fd(dir, 1);
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}
