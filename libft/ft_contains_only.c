/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contains_only.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:54:08 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 16:02:16 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_contains_only(char *str, char c)
{
	int	cur;

	cur = -1;
	while (str[++cur])
		if (str[cur] != c)
			return (0);
	return (1);
}
