/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:52:22 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 03:48:26 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	set_exit_status(130);
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	child_signal_handler(int signal)
{
	if (signal == SIGQUIT)
	{
		set_exit_status(131);
		return (ft_putendl_fd("Quit (core dumped)", 1));
	}
	if (signal != SIGINT)
		return ;
	set_exit_status(130);
	ft_putchar_fd('\n', 1);
}

void	heredoc_signal_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	set_exit_status(130);
	ft_putstr_fd("\1\n", STDIN_FILENO);
}
