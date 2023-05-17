/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 04:00:25 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:00:27 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Matrix is expected to be NULL terminated.
void	ft_free_char_matrix(char ***m)
{
	size_t	i;

	i = 0;
	while (*(*m + i) != NULL)
	{
		free(*(*m + i));
		*(*m + i) = NULL;
		i++;
	}
	free(*m);
	*m = NULL;
}
