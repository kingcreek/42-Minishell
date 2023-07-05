/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: imurugar <imurugar@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/16 16:51:47 by imurugar		  #+#	#+#			 */
/*   Updated: 2023/07/05 20:01:16 by imurugar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

static t_var	**get_environment_lst(char **envp)
{
	t_var	**env_lst;
	char	*eq_sign;
	size_t	inx;

	inx = 0;
	env_lst = malloc(sizeof(t_var *));
	*env_lst = NULL;
	while (envp[inx])
	{
		eq_sign = ft_strchr(envp[inx], '=');
		var_lst_add_front(env_lst, var_lst_new(
				ft_substr(envp[inx], 0, eq_sign - envp[inx]),
				ft_substr(eq_sign, 1, ft_strlen(eq_sign + 1))
				));
		inx++;
	}
	return (env_lst);
}

void init(char **envp)
{
	char *std_in;
	char *shell_name;
	t_shell st_shell;

	shell_name = LULUSHELL;
	g_env = get_environment_lst(envp);
	set_exit_status(EXIT_SUCCESS);
	sig_setup();
	int saved_stdin = dup(STDIN_FILENO);
	int saved_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		std_in = readline(shell_name);
		if (std_in == NULL)
		{
			ft_putendl_fd("exit", 1);
			break;
		}
		add_history(std_in);
		parsing(std_in, &st_shell);
		free(std_in);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
	}
	rl_clear_history();
	close(saved_stdin);
	close(saved_stdout);
}

void	set_exit_status(int exit_status)
{
	var_lst_add_var(g_env, var_lst_new(ft_strdup("?"), ft_itoa(exit_status)));
}

void	set_in_out(t_shell *st_shell)
{
	st_shell->error_locale = NULL;
	st_shell->file_stat = 0;
	st_shell->infile = STDIN_FILENO;
	st_shell->outfile = STDOUT_FILENO;
	if (st_shell->lst_size != 1)
	{
		if (st_shell->lst_inx == 1)
		{
			pipe(st_shell->pipe);
			st_shell->outfile = st_shell->pipe[STDOUT_FILENO];
		}
		else if (st_shell->lst_inx != st_shell->lst_size)
		{
			st_shell->infile = st_shell->pipe[STDIN_FILENO];
			close(st_shell->pipe[STDOUT_FILENO]);
			pipe(st_shell->pipe);
			st_shell->outfile = st_shell->pipe[STDOUT_FILENO];
		}
		else
			st_shell->infile = st_shell->pipe[STDIN_FILENO];
	}
}
