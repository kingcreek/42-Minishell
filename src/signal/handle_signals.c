/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 10:07:38 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/08 00:54:58 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\nCaught SIGINT signal\n"); // Manejar la interrupción (Ctrl + C) aquí
		exit(EXIT_SUCCESS);
	}
	else if (signal == SIGQUIT)
	{
		printf("\nCaught SIGQUIT signal\n"); // Manejar la finalización forzada (Ctrl + \) aquí
		return ;
	}
	/*else if (signal == SIGTSTP)
	{
		printf("\nCaught SIGTSTP signal\n"); // Manejar la suspensión (Ctrl + Z) aquí
	}*/
	/*else if (signal == SIGCHLD)
	{
		printf("\nCaught SIGCHLD signal\n"); // Manejar el fin de un proceso hijo aquí
		while (waitpid(-1, NULL, WNOHANG) > 0)
		{
			// Limpie los procesos zombies
		}
	}*/
	if (signal == SIGTERM)
	{
		printf("\nCaught SIGTERM signal\n"); // Manejar la señal de terminación aquí
		exit(EXIT_SUCCESS);
	}
}

void	start_handles(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	//signal(SIGTSTP, handle_signal);
	signal(SIGCHLD, handle_signal);
	signal(SIGTERM, handle_signal);
}
