/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:39:10 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 17:40:30 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	index_of(char *str, char *search, int len)
{
	int	cur;
	int	s_len;

	cur = 0;
	s_len = ft_strlen(search);
	while (str[cur])
	{
		if (ft_strncmp(str + cur, search, s_len) == 0)
			len--;
		if (len <= 0)
			return (cur);
		cur++;
	}
	return (cur);
}

int	index_new_line(char *str)
{
	int	idx;
	int	tmp;

	idx = index_of(str, " ", 1);
	tmp = index_of(str, "\t", 1);
	if (tmp || str[0] == '\t')
		if (tmp < idx)
			idx = tmp;
	return (idx);
}

int	outlst_len(t_o_file *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
