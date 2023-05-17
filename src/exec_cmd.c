/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:51:58 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:15:47 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_environment(void)
{
	t_var	*iterator;
	size_t	inx;
	char	*aux;
	char	**envp;

	inx = 0;
	iterator = *g_env;
	envp = malloc(var_lst_size(*g_env) * sizeof(char *));
	while (iterator)
	{
		if (ft_strncmp(iterator->name, "?", 2) != 0 && iterator->value != NULL)
		{
			aux = ft_strjoin(iterator->name, "=");
			envp[inx] = ft_strjoin(aux, iterator->value);
			free(aux);
			inx++;
		}
		iterator = iterator->next;
	}
	envp[inx] = NULL;
	return (envp);
}

static void	wait_for_child(int pid, t_shell *st_shell)
{
	int		exit_status;

	exit_status = 0;
	waitpid(pid, &exit_status, 0);
	waitpid(pid, &exit_status, 0);
	if (!WIFSIGNALED(exit_status))
	{
		st_shell->exit_status = WEXITSTATUS(exit_status);
		set_exit_status(WEXITSTATUS(exit_status));
	}
}

static t_bool	is_dir(t_pipe *pipe_lst)
{
	DIR		*dir;
	char	**cmds;

	cmds = ft_word_split(pipe_lst->str, ft_isspace);
	dir = opendir(cmds[0]);
	if (dir != NULL)
	{
		closedir(dir);
		if ((ft_strlen(cmds[0]) > 1 && cmds[0][ft_strlen(cmds[0]) - 1] == '/')
			|| (cmds[0][0] == '.' && cmds[0][1] == '/') || cmds[0][0] == '/')
		{
			generic_error(126, cmds[0], "Is a directory");
			ft_free_char_matrix(&cmds);
		}
		else
		{
			ft_free_char_matrix(&cmds);
			return (FALSE);
		}
		return (TRUE);
	}
	ft_free_char_matrix(&cmds);
	return (FALSE);
}

void	fork_exec(t_shell *st_shell, t_pipe *pipe_lst)
{
	int		pid;
	char	**envp;

	child_sig_setup();
	if (is_dir(pipe_lst) == TRUE)
		return ;
	envp = get_environment();
	if (recognizer_cmd(pipe_lst, st_shell) == FALSE)
		return (ft_free_char_matrix(&envp));
	pid = fork();
	if (pid == 0)
		exec(st_shell, envp, pipe_lst);
	if (st_shell->lst_inx == st_shell->lst_size)
	{
		close_pipes(st_shell);
		wait_for_child(pid, st_shell);
	}
	ft_free_char_matrix(&envp);
	ft_free_char_matrix(&st_shell->args);
	free(st_shell->cmd);
}

void	exec(t_shell *st_shell, char **envp, t_pipe *pipe_lst)
{
	dup2(st_shell->infile, STDIN_FILENO);
	dup2(st_shell->outfile, STDOUT_FILENO);
	close_fds(st_shell);
	execve(st_shell->cmd, st_shell->args, envp);
	free(st_shell->cmd);
	ft_free_char_matrix(&envp);
	ft_free_char_matrix(&st_shell->args);
	ft_exit("exit", pipe_lst, NULL, FALSE);
}
