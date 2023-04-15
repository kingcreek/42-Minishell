/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:02:51 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/15 11:50:17 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_str(char **lst)
{
	char	*n1;

	if (!lst)
		return ;
	while (*lst)
	{
		n1 = *lst;
		lst++;
		free(n1);
	}
	*lst = NULL;
}

void	free_envs(t_envs **s)
{
	t_envs	*tmp;

	if (s)
	{
		while (*s)
		{
			tmp = (*s)->next;
			free(*s);
			(*s) = tmp;
		}
	}
}

int	free_t_mini(t_mini *mini)
{
	int	exit_status;

	exit_status = mini->exit_status;
	free_envs(&mini->envs);
	return (exit_status);
}

int	strarr_free(char **arr)
{
	int	cur;

	cur = -1;
	if (arr)
	{
		while (arr[++cur])
			free(arr[cur]);
		free(arr);
	}
	return (0);
}

int	lst_clear(t_list **lst)
{
	t_list	*nxt;

	while (*lst)
	{
		nxt = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = nxt;
	}
	*lst = NULL;
	return (0);
}

