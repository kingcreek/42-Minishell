/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:01 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/18 05:12:59 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(int write_fd)
{
	t_var	*iterator;

	iterator = *g_env;
	if (!iterator || !var_lst_find_var("PATH", iterator))
	{
		set_exit_status(127);
		return (ft_putendl_fd("env: No such file or directory", 2));
	}
	while (iterator)
	{
		if (ft_strncmp(iterator->name, "?", 2) != 0 && iterator->value != NULL)
		{
			ft_putstr_fd(iterator->name, write_fd);
			ft_putstr_fd("=", write_fd);
			ft_putendl_fd(iterator->value, write_fd);
		}
		iterator = iterator->next;
	}
	set_exit_status(EXIT_SUCCESS);
}
