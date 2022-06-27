/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_buil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:38:03 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/15 20:17:14 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		write(STDOUT_FILENO, "declare -x ", 12);
		while (env[i][j] != '=' && env[i][j])
		{
			ft_putchar_fd(env[i][j], STDOUT_FILENO);
			j++;
		}
		write(STDOUT_FILENO, "=", 1);
		if (env[i][j] == '=')
			j++;
		write(STDOUT_FILENO, "\"", 1);
		ft_putstr_fd(env[i] + j, STDOUT_FILENO);
		write(STDOUT_FILENO, "\"\n", 2);
		i++;
	}
}

static void	alpha_sorter(char **env, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[count])
		count++;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = ft_strdup(env[i]);
				free(env[i]);
				env[i] = ft_strdup(env[j]);
				free(env[j]);
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	print_env(env);
}

static int	valid_name(char *name)
{
	int	i;

	i = 0;
	if (!*name || ft_isdigit(*name))
	{
		write(STDOUT_FILENO, "export: not a valid identifier\n", 32);
		g_lsig = 1;
		return (1);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			write(STDOUT_FILENO, "export: ", 9);
			ft_putstr_fd(name, STDOUT_FILENO);
			write(STDOUT_FILENO, ": not a valid identifier\n", 25);
			g_lsig = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	adding_shit(int i, char **commands, char *aux, t_list **lst_env)
{
	int	j;

	j = 0;
	while (j < i)
	{
		aux = ft_strchr(commands[j], '=');
		if (aux)
		{
			*aux = '\0';
			aux++;
		}
		if (valid_name(commands[j]))
			return (1);
		set_value(lst_env, commands[j], aux);
		if (aux)
		{
			aux--;
			*aux = '=';
		}
		j++;
	}
	return (0);
}

void	export_buil(char **commands, t_list **lst_env, char **env, int mode)
{
	int		i;
	char	*aux;

	if (*commands && !mode)
	{
		i = 0;
		while (commands[i])
			i++;
		aux = NULL;
		if (!adding_shit(i, commands, aux, lst_env))
			g_lsig = 0;
		return ;
	}
	alpha_sorter(env, 0);
	if (mode)
		exit(0);
	return ;
}
