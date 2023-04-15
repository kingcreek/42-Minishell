/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:19:17 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/15 11:19:46 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_simbol(char c)
{
	if (c == '\'' || c == '"' || c == '<'
		|| c == '&' || c == '|' || c == '>' || c == ';')
		return (1);
	return (0);
}