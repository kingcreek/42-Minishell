/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:13:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/06 21:35:27 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function handles different signals,
 * such as SIGINT, SIGQUIT, SIGTSTP, SIGCHLD, and SIGTERM,
 * and performs specific actions for each signal.
 * 
 * @param signal The signal parameter is an integer
 * that represents the signal that was caught by the
 * program. It is used to determine which signal was
 * received and to execute the appropriate code to
 * handle that signal.
 */
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
	}
	else if (signal == SIGTSTP)
	{
		printf("\nCaught SIGTSTP signal\n"); // Manejar la suspensión (Ctrl + Z) aquí
	}
	else if (signal == SIGCHLD)
	{
		printf("\nCaught SIGCHLD signal\n"); // Manejar el fin de un proceso hijo aquí
		while (waitpid(-1, NULL, WNOHANG) > 0)
		{
			// Limpie los procesos zombies
		}
	}
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
	signal(SIGTSTP, handle_signal);
	signal(SIGCHLD, handle_signal);
	signal(SIGTERM, handle_signal);
}

int	main(int argc, char **argv, char **envp)
{
	char			*rd_line;

	if (argc > 1)
	{
		printf("No se necesitan parametros?");
		exit(EXIT_FAILURE);
	}
	(void)argv;
	(void)envp;
	start_handles();

	while (1)
	{
		rd_line = readline("ArIm$ ");
		if (!rd_line)
		{
			printf("exit\n");
			exit (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}