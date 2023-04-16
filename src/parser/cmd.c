/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:20:18 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/16 16:29:55 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmd_list(t_cmdlst **command_list, t_list *args)
{
	t_cmdlst	*new;

	*command_list = NULL;
	while (args && !get_arg_type(args->content))
	{
		printf("%s\n", (char *)args->content);
		if (args)
			args = args->next;
	}
	return (1);
}
