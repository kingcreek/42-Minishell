/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_lst_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:52:38 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 03:48:22 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_lst_delete_node(t_pipe *node)
{
	if (!node)
		return ;
	free(node->str);
	free(node);
}

void	pipe_lst_clear(t_pipe **lst)
{
	t_pipe	*acc;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		acc = (*lst)->next;
		pipe_lst_delete_node(*lst);
		*lst = acc;
	}
	*lst = NULL;
}
