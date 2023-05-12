/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:10:15 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/12 14:10:16 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *s1, int c)
{
	char	*dst;
	size_t	len;

	len = 0;
	while (s1[len] && s1[len] != c)
		len++;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	while (len-- > 0)
		dst[len] = s1[len];
	return (dst);
}
