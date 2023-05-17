/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 04:01:03 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:01:05 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *s)
{
	long long	num;
	long long	sign;

	num = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == 45)
		sign = -1;
	if (*s == 43 || *s == 45)
		s++;
	while (*s >= 48 && *s <= 57)
	{
		num = 10 * num + *s - 48;
		s++;
	}
	return (num * sign);
}
