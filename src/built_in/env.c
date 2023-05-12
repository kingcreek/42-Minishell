/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:10:03 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/11 14:11:25 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *mini)
{
	t_envs	*curr;

	curr = mini->envs;
	while (curr)
	{
		ft_putstr_fd(curr->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(curr->val, 1);
		curr = curr->next;
	}
}
