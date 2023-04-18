/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:10:03 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 16:10:50 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_vars(t_mini *mini)
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
