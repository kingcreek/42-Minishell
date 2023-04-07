/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:22:07 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/07 10:13:41 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int err, char *s)
{
	if (err == ERR_CMD)
	{
		printf("%s: command not found\n", s);
		exit(127);
	}
	else if (err == ERR_MALLOC)
	{
		printf("Memory allocation fails.\n");
		exit(1);
	}
	/*
	unlink(".tmp");
	g_state.exit_code = 1;
	ft_putstr_fd("minishell: ", 2);
	if (Flag == 0)
	{
		ft_putstr_fd("Memory allocation fails.\n", 2);
		exit(1);
	}
	else if (Flag == 1)
	{
		g_state.exit_code = 127;
		ft_eprintf("%s: command not found\n", s);
		exit(127);
	}
	else if (Flag == 2)
	{
		perror(s);
		exit(1);
	}
	else if (Flag == 3)
	{
		ft_eprintf("%s\n", s);
		exit(1);
	}
	*/
}