/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 21:22:07 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/13 14:22:31 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(int error_code, char *content)
{
	if (error_code == 1)
	{
		printf("\033[91m%s\033[0m\n",
			"minishell: parse error, quotes are never closed");
	}
	else if (error_code == 2)
	{
		printf("\033[91m%s '%s'\033[0m\n",
			"minishell: parse error, near", content);
	}
	else if (error_code == 3)
	{
		printf("\033[91m%s '%s'\033[0m\n",
			"minishell: the command cannot end with",
			content);
	}
	return (1);
}
