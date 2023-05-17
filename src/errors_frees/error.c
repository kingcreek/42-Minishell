/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:27 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 06:13:43 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_syntax(char *str)
{
	int	inx;

	inx = 0;
	if (str[inx] == '\0')
	{
		ft_putstr_fd(MINISHELL_ERROR, 2);
		ft_putstr_fd(SYNTAX_ERROR, 2);
		ft_putendl_fd("`newline'", 2);
		set_exit_status(2);
		return (FALSE);
	}
	if (ft_strchr("<>", str[inx]))
	{
		ft_putstr_fd(MINISHELL_ERROR, 2);
		ft_putstr_fd(SYNTAX_ERROR, 2);
		ft_putstr_fd("`", 2);
		ft_putchar_fd(str[inx], 2);
		ft_putendl_fd("'", 2);
		set_exit_status(2);
		return (FALSE);
	}
	return (TRUE);
}

void	pipe_syntax_error(void)
{
	ft_putstr_fd(MINISHELL_ERROR, 2);
	ft_putstr_fd(SYNTAX_ERROR, 2);
	ft_putendl_fd("`|'", 2);
	set_exit_status(2);
}

t_bool	generic_error(int exit_status, char *locale, char *message)
{
	ft_putstr_fd(MINISHELL_ERROR, STDERR_FILENO);
	if (locale)
	{
		ft_putstr_fd(locale, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
	set_exit_status(exit_status);
	return (FALSE);
}

void	quotes_error(void)
{
	ft_putstr_fd(MINISHELL_ERROR, 2);
	ft_putstr_fd("error while looking for matching quote\n", STDERR_FILENO);
}
