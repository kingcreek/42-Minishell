/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:24:42 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/12 16:25:03 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup_end(const char *s1, int c)
{
	char	*dst;
	size_t	len;
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] != c)
		i++;
	len = i + 1;
	dst = (char *)malloc(len);
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	while (i-- > 0)
		dst[i] = s1[i];
	return (dst + len - 1);
}