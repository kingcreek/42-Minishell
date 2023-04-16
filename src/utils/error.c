/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:22:07 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/16 16:03:54 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(int error_code, char *content)
{
	if (error_code == 1)
	{
		printf(COLOR_RED "minishell: parse error, quotes are never closed" COLOR_RESET "\n");
	}
	else if (error_code == 2)
	{
		printf(COLOR_RED "minishell: parse error, near '%s'" COLOR_RESET "\n", content);
	}
	else if (error_code == 3)
	{
		printf(COLOR_RED "minishell: the command cannot end with '%s'" COLOR_RESET "\n", content);
	}
	return (1);
}
