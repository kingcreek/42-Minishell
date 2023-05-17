/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:29 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/16 16:54:31 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recognize_builds(char *usr_in, t_builtin *builds)
{
	char	**words;
	char	*temp;
	int		build_inx;
	int		inx;

	inx = 0;
	words = ft_word_split(usr_in, ft_isspace);
	if (!words)
		return (7);
	temp = remove_quotes_from_word(words[inx], ft_strlen(words[inx]));
	build_inx = hash_search(temp, builds);
	free(temp);
	if (build_inx != 7)
	{
		ft_free_char_matrix(&words);
		return (build_inx);
	}
	ft_free_char_matrix(&words);
	return (build_inx);
}

void	exec_builds(t_builtin *builds, int build_inx, t_pipe *pipe_lst,
	t_shell *st_shell)
{
	if (build_inx == 1 || build_inx == 2)
		builds[build_inx].func(st_shell->outfile);
	else if (build_inx == 4)
		builds[build_inx].func(pipe_lst->str, pipe_lst, builds);
	else if (build_inx == 0 || build_inx == 5)
		builds[build_inx].func(pipe_lst->str, st_shell->outfile);
	else
		builds[build_inx].func(pipe_lst->str);
}

void	fork_exec_builds(t_builtin *builds, int build_inx, t_pipe *pipe_lst,
	t_shell *st_shell)
{
	int			pid;
	int			exit_status;

	pid = fork();
	if (pid == 0)
	{
		dup2(st_shell->infile, STDIN_FILENO);
		dup2(st_shell->outfile, STDOUT_FILENO);
		close_fds(st_shell);
		exec_builds(builds, build_inx, pipe_lst, st_shell);
		ft_exit("exit", pipe_lst, builds, FALSE);
	}
	if (st_shell->lst_inx == st_shell->lst_size)
	{
		close_pipes(st_shell);
		waitpid(pid, &exit_status, 0);
		st_shell->exit_status = WEXITSTATUS(exit_status);
		set_exit_status(WEXITSTATUS(exit_status));
	}
}

t_bool	is_builds(t_pipe *pipe_lst, t_shell *st_shell)
{
	int			build_inx;
	t_builtin	*builds;

	builds = init_builds();
	build_inx = recognize_builds(pipe_lst->str, builds);
	if (build_inx == 7)
	{
		free(builds);
		return (FALSE);
	}
	if (st_shell->lst_size == 1)
		exec_builds(builds, build_inx, pipe_lst, st_shell);
	else
		fork_exec_builds(builds, build_inx, pipe_lst, st_shell);
	free(builds);
	return (TRUE);
}
