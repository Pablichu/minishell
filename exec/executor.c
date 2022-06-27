/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 20:01:15 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/11/16 18:25:26 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**paths(char **env, char *cmd)
{
	int		i;
	char	*aux;
	char	**paths;

	i = 0;
	paths = NULL;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH=", 5)))
		{
			aux = env[i];
			paths = ft_split(aux + 5, ':');
			i = 0;
			while (paths[i])
			{
				aux = ft_strjoin(paths[i], cmd);
				free(paths[i]);
				paths[i] = aux;
				i++;
			}
			break ;
		}
		i++;
	}
	return (paths);
}

void	cmd_exe(char **commands, char **mi_env)
{
	int		i;
	char	*aux;
	char	**path;

	execve(commands[0], commands, mi_env);
	aux = ft_strjoin("/", commands[0]);
	path = NULL;
	path = paths(mi_env, aux);
	if (!path)
		exit(4);
	free(aux);
	i = 0;
	while (path[i])
	{
		if ((execve(path[i], commands, mi_env)) != -1)
			break ;
		i++;
	}
	ft_freee(path);
	exit(4);
}

void	builtin_check(t_token *aux, t_shell *mini)
{
	if (!ft_strncmp(aux->argv[0], "cd", 3))
		cd_buil(aux->argv[1], mini->env_list, 1);
	else if (!ft_strncmp(aux->argv[0], "echo", 5))
		echo_buil(aux->command, mini->env_list);
	else if (!ft_strncmp(aux->argv[0], "pwd", 4))
		pwd_buil();
	else if (!ft_strncmp(aux->argv[0], "export", 7))
		export_buil(aux->argv + 1, NULL, mini->mi_env, 1);
	else if (!ft_strncmp(aux->argv[0], "env", 4))
		env_buil(mini->mi_env);
	else if (!ft_strncmp(aux->argv[0], "exit", 5))
		exit_buil(mini->num_pipes, aux->argv);
	else
		cmd_exe(aux->argv, mini->mi_env);
	exit(0);
}

static void	handler(int sig)
{
	if (sig == 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		g_lsig = -50;
	}
	if (sig == 3)
	{
		write(STDOUT_FILENO, "Quit: 3\n", 8);
		g_lsig = -100;
	}
}

void	executer(t_shell *mini)
{
	int		error;
	int		stdback[2];
	t_token	*aux;
	t_list	*lst_aux;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	error = 0;
	stdback[0] = dup(STDIN_FILENO);
	stdback[1] = dup(STDOUT_FILENO);
	lst_aux = mini->token_list;
	aux = lst_aux->content;
	if (mini->num_pipes)
		error = patter(aux, lst_aux, mini);
	else
		error = one_command(aux, mini);
	dup2(stdback[0], STDIN_FILENO);
	dup2(stdback[1], STDOUT_FILENO);
	close(stdback[0]);
	close(stdback[1]);
	end_process(error, mini);
}
