/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:13:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/07 10:07:54 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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