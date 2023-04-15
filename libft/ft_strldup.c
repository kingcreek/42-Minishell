/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:52:10 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/15 11:55:12 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *s1, int size)
{
	int		len;
	char	*ret;

	len = ft_strlen(s1);
	if (len > size)
		len = size;
	ret = (char *)malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	ret[len] = 0;
	while (--len >= 0)
		ret[len] = s1[len];
	return (ret);
}
