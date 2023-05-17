/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:52:11 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 03:48:56 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	var_lst_size(t_var *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_var	*var_lst_find_var(char *name, t_var *lst)
{
	while (lst)
	{
		if (ft_strncmp(name, lst->name, ft_strlen(name) + 1) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
