/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_and_closes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:32 by imurugar          #+#    #+#             */
/*   Updated: 2023/07/05 19:20:39 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_shell *st_shell)
{
	if (st_shell->lst_size != 1)
	{
		if (st_shell->lst_inx == 1)
			close(st_shell->pipe[STDIN_FILENO]);
		if (st_shell->lst_inx == st_shell->lst_size)
			close(st_shell->pipe[STDOUT_FILENO]);
	}
}

void	close_pipes(t_shell *st_shell)
{
	if (st_shell->lst_size != 1)
	{
		close(st_shell->pipe[0]);
		close(st_shell->pipe[1]);
	}
}

void	cmd_error(t_shell *st_shell, char **paths)
{
	ft_putstr_fd(MINISHELL_ERROR, STDERR_FILENO);
	ft_putstr_fd(st_shell->args[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	ft_free_char_matrix(&st_shell->args);
	if (paths)
		ft_free_char_matrix(&paths);
}

void	free_args_error(t_shell *st_shell, char *message)
{
	ft_putstr_fd(MINISHELL_ERROR, STDERR_FILENO);
	ft_putstr_fd(st_shell->args[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	ft_free_char_matrix(&st_shell->args);
}

t_bool	free_return(char *str_free)
{
	free(str_free);
	sig_setup();
	return (FALSE);
}
