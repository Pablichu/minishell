/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 20:06:17 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/12/08 18:37:26 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termcap.h>
# include <termios.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include "libft.h"
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>

# define CTRL_D		4
# define CTRL_C		3
# define CTRL_L		12
# define CTRL_4		28

int	g_lsig;

typedef struct s_env
{
	char	*name;
	char	*value;
}				t_env;

typedef struct s_pipes
{
	int		i;
	int		spipe;
	int		fpipe[2];
}				t_pipes;

typedef struct s_hist
{
	char	*line;
	char	*original;
	int		pos;
}				t_hist;

typedef struct s_token
{
	char	*str;
	char	*command;
	char	*file_in;
	char	*db_inp;
	int		input;
	int		fd_in;
	char	*file_out;
	int		output;
	int		fd_out;
	int		not_arg;
	char	**argv;
	pid_t	pid;
}				t_token;

typedef struct s_split
{
	int		j;
	int		k;
	int		words;
	int		lenw;
	char	what;
	char	*aux;
	char	*vble;
	char	*vble2;
	char	*name;
	char	*result;
	char	*temp;
	char	*after;
}				t_split;

typedef struct s_aux
{
	char	*str;
	char	*backup_str;
	char	*begin_token;
	t_token	*node;
	char	*join;
	char	*join2;
	char	maybe[2];
	char	*temp;
	char	*before;
	char	*dollar;
	char	*after;
	char	*medium;
	char	*aux;
	char	*quote;
	char	*name;
	int		num;
	int		len;
	char	what;
	char	save;
	char	redir;
	int		redir_in;
	char	bkp_line[1024];
	int		count_skip;
	int		j;
	char	*var1;
	char	*var2;
	t_list	*tok_list;
	char	*bkp;
}				t_aux;

typedef struct s_shell
{
	int				ret;
	char			buff[5];
	char			*term_name;
	char			buff_line[1024];
	char			*buff_pos;
	char			*buff_temp;
	t_list			*historial_list;
	t_list			*env_list;
	t_list			*token_list;
	struct termios	termios_new;
	struct termios	termios_backup;
	int				updown;
	int				pos_hist;
	char			**argv;
	int				argc;
	char			**mi_env;
	int				error;
	int				errno;
	int				num_pipes;
	char			*str_redir;
	int				quote;
	int				dquote;
	int				dollar;
	int				fail_pipe;
	int				delimit;
}				t_shell;

t_env	*new_vble(char *name, char *value);
void	env_to_list(char **env, t_shell *mini);
char	**list_to_env(char **mi_env, t_list *env);
char	*get_value(t_list *env, char *name);
void	set_value(t_list **env, char *name, char *value);
void	del_env_content(void *node);
void	del_token_content(void *node);

//termcaps
int		read_function(t_shell *mini);
void	init_termcap(t_shell *mini);
int		read_line(t_shell *mini);

//historial
void	add_historial(char *str, t_list **list_hist);
void	del_hist_content(void *node);
char	*hist_up(char *buff_line, char **buff_temp, int *updown, t_list *hist);
char	*hist_down(char *buff_line, char *buff_temp, int *updown, t_list *hist);
void	*update_hist(char *buff_line, int pos, t_list *historial);

//parser
void	update_node(t_list *list);
char	*skip_quotes(char *str, t_shell *mini, char quote, int *len);
char	*expand(char *str, t_shell *mini);
char	calc_char(char *dest, char source);
char	*init_values_dollar(t_shell *mini, t_aux *aux, char *str);
char	*init_values_quote(t_shell *mini, t_aux *aux, char *str);
char	*init_values_dquote(t_shell *mini, t_aux *aux, char *str);
char	*check_more_dollar(char *str, t_shell *mini);
char	*not_more_dollar(char *str, t_split *aux, t_shell *mini);
void	more_dollar(char *str, t_split *aux, t_shell *mini);
void	check_vble_name(char *str, t_split *aux);
void	set_values_aux_result(t_split *aux);
void	get_value_aux_what(t_split *aux);
void	set_value_aux_what(t_split *aux);
int		token(t_shell *mini);
void	print_env_list(t_list *env, const char *fn);
int		parse_pipe(t_shell *mini);
int		parse_redir(t_shell *mini, t_list *lst);
char	*get_file(t_shell *mini, t_token *node, char **file, int c);
void	not_args_maybe_redir(t_aux *aux, char **file, int *not_arg);
void	exist_file(t_shell *mini, char c, t_token *node);
void	delimit(t_shell *mini, char *limit);
char	*advance_limit(char *limit, int *i, char *temp);
char	*join_command(t_token *node, char *str, int c);
int		count_words(t_shell *mini, char *s);
int		len_words(t_shell *mini, char *s);
char	**turbosplit(t_shell *mini, char *s);
void	if_dollar(char c, t_shell *mini);
char	*skip_spaces(char *str);
void	define_and_free(char *out, char *in);
void	def_and_free(t_token *node, char *bk_str);

//exec
void	file_dup(t_token *aux);
void	executer(t_shell *mini);
void	end_process(int error, t_shell *mini);
void	cmd_exe(char **commands, char **mi_env);
int		one_command(t_token *aux, t_shell *mini);
void	builtin_check(t_token *aux, t_shell *mini);
int		patter(t_token *aux, t_list *lst_aux, t_shell *mini);

//builtins
void	pwd_buil(void);
void	env_buil(char **env);
int		bye_echo_problem(char *args);
void	exit_buil(int pipes, char **argv);
void	echo_buil(char *args, t_list *env_lst);
void	print_dollar(char *args, int *i, t_list *env_lst, int mode);
int		cd_buil(char *command, t_list *env_lst, int mode);
void	export_buil(char **commands, t_list **lst_env, char **env, int mode);
char	**unset_buil(char **commands, char **mi_env, t_list *lst_env, int mode);

//free
void	del_env(void *content);

//error
#endif
