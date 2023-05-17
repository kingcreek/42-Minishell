/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 04:05:29 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:05:31 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Matrix is expected to be NULL terminated.
void	ft_free_matrix(void ***p, size_t line_count)
{
	size_t	i;

	i = 0;
	while (i < line_count && *(*p + i) != NULL)
	{
		free(*(*p + i));
		*(*p + i) = NULL;
		i++;
	}
	free(*p);
	*p = NULL;
}
