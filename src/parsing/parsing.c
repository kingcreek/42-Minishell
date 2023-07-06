/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:43 by imurugar          #+#    #+#             */
/*   Updated: 2023/07/06 13:42:48 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipes(t_pipe *pipe_lst)
{
	int		count;
	t_pipe	*current;

	count = 0;
	current = pipe_lst;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	parsing_loop_h(t_pipe *pipe_lst, t_shell *st_shell, int pipe_count)
{
	int		stat;

	stat = recognize_redirect(pipe_lst, st_shell);
	find_var_and_expand(&pipe_lst->str, FALSE);
	if (is_empty_str(pipe_lst->str))
		st_shell->exit_status = EXIT_SUCCESS;
	else if (stat == EXIT_SUCCESS && is_builds(pipe_lst, st_shell) == FALSE)
	{
		fork_exec(st_shell, pipe_lst);
		if (st_shell->lst_inx != pipe_count)
		{
			close(st_shell->infile);
			close(st_shell->outfile);
		}
	}
	else if (stat == -1)
		return (pipe_lst_clear(&pipe_lst));
}

void	parsing_loop(t_pipe *pipe_lst, t_shell *st_shell)
{
	t_pipe	*aux;
	int		pipe_count;

	pipe_count = count_pipes(pipe_lst);
	while (pipe_lst)
	{
		set_in_out(st_shell);
		if (is_empty_str(pipe_lst->str))
		{
			st_shell->exit_status = EXIT_SUCCESS;
		}
		else
		{
			parsing_loop_h(pipe_lst, st_shell, pipe_count);
		}
		aux = pipe_lst;
		pipe_lst = pipe_lst->next;
		pipe_lst_delete_node(aux);
		st_shell->lst_inx++;
	}
}

void	parsing(char *std_in, t_shell *st_shell)
{
	t_pipe	*pipe_lst;

	pipe_lst = pipe_parse(std_in, st_shell);
	if (!pipe_lst)
		return ;
	st_shell->lst_inx = 1;
	st_shell->exit_status = -1;
	parsing_loop(pipe_lst, st_shell);
	st_shell->lst_inx = 1;
	while (st_shell->lst_inx <= st_shell->lst_size)
	{
		waitpid(-1, NULL, 0);
		st_shell->lst_inx++;
	}
	if (st_shell->exit_status != -1)
		set_exit_status(st_shell->exit_status);
	sig_setup();
}
