/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:18:59 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 16:08:49 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit(t_cmdlst *lst)
{
	if ((ft_strcmp(lst->command, "exit") == 0) && ((lst->todo_next == 0
				&& cmdlist_len(lst) == 1) || lst->todo_next == 2
			|| lst->todo_next == 3))
		return (1);
	return (0);
}
