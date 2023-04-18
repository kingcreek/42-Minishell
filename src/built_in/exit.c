/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:21:44 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 21:57:37 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_mini *mem, t_cmdlst *lst)
{
	int		exit_status;

	exit_status = 0;
	cmd_clear(&lst);
	exit(free_t_mini(mem, exit_status));
}
