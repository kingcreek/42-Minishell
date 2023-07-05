/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:51:38 by imurugar          #+#    #+#             */
/*   Updated: 2023/07/05 21:02:32 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	**g_env;

int	main(int argc, char **argv, char **envp)
{
	int		exit_code;

	if (!argv || argc != 1)
		return (EXIT_FAILURE);
	init(envp);
	exit_code = get_exit_status();
	var_lst_clear(g_env);
	free(g_env);
	return (exit_code);
}

int	get_exit_status(void)
{
	t_var	*current_status;
	int		exit_code;

	current_status = var_lst_find_var("?", *g_env);
	if (!current_status)
		return (EXIT_FAILURE);
	exit_code = ft_atoi(current_status->value);
	return (exit_code);
}

/*

archivos modificados:
init.c en la funcion init
archivo export y el que he creado para ordenar la lista
archivo parsing

*/