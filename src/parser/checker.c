/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:14:25 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/13 14:35:08 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *cmd)
{
	int	len;
	int	single_quotes;
	int	double_quotes;
	int	i;

	len = strlen(cmd);
	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (i < len)
	{
		if (cmd[i] == '\'')
		{
			single_quotes++;
		}
		else if (cmd[i] == '\"')
		{
			double_quotes++;
		}
		i++;
	}
	i = ((single_quotes % 2 == 0) && (double_quotes % 2 == 0)) == 0;
	if (i != 0)
		print_error(1, NULL);
	return (i);
}

int	check_specials(t_list *args)
{
	t_list	*it_args;
	int		is_special;

	it_args = args;
	is_special = 0;
	while (it_args)
	{
		if (is_sep(it_args->content))
		{
			if (is_special)
				return (print_error(2, it_args->content));
			is_special = 1;
		}
		else
			is_special = 0;
		if (!it_args->next)
		{
			if (is_sep(it_args->content) && strcmp_len(it_args->content, ";"))
				return (print_error(3, it_args->content));
		}
		it_args = it_args->next;
	}
	return (0);
}
