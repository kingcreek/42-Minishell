/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:05:38 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/15 13:12:55 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end_queotes(char *str, int end)
{
	int	end_idx;

	end_idx = -2;
	if (str[0] == '\'')
		end_idx = get_end_arg(str, index_of(str + 1, "'", 1) + 2);
	else if (end > -1 && index_of(str, "'", 1) < end)
		end_idx = get_end_arg(str, index_of(str + 1, "'", 2) + 2);
	else if (str[0] == '"')
		end_idx = get_end_arg(str, index_of(str + 1, "\"", 1) + 2);
	else if (end > -1 && index_of(str, "\"", 1) < end)
		end_idx = get_end_arg(str, index_of(str + 1, "\"", 2) + 2);
	return (end_idx);
}

int	get_end_arg(char *str, int quote_idx)
{
	char	**split;
	int		end_idx;
	int		tmp;
	int		cur;

	split = ft_split("&& || | << < >> > & ;", ' ');
	if (!split)
		return (0);
	end_idx = index_new_line(str + quote_idx);
	cur = -1;
	while (split[++cur])
	{
		tmp = index_of(str + quote_idx, split[cur], 1);
		if (tmp < end_idx)
		{
			strarr_free(split);
			return (tmp + quote_idx);
		}
	}
	strarr_free(split);
	return (end_idx + quote_idx);
}

int	get_end_index(char *str, int end)
{
	int		end_idx;
	char	**split;
	int		cur;

	if (end == 0)
		return (0);
	split = ft_split("&& || | << < >> > & ;", ' ');
	if (!split)
		return (0);
	end_idx = get_end_queotes(str, end);
	if (end_idx == 0)
		return (strarr_free(split));
	if (end_idx != -2)
		return (end_idx + strarr_free(split));
	cur = -1;
	while (split[++cur])
	{
		if ((end > -1 && index_of(str, split[cur], 1) < end))
			return (index_of(str, split[cur], 1) + strarr_free(split));
		if (index_of(str, split[cur], 1) == 0)
			return (ft_strlen(split[cur]) + strarr_free(split));
	}
	return (end + strarr_free(split));
}

int	split_args(t_list **args, char *cmd)
{
	int		cur;
	char	*arg;
	int		end_idx;

	cur = -1;
	while (cmd[++cur])
	{
		if (cmd[cur] == ' ' || cmd[cur] == '\t')
			continue ;
		if (is_simbol(cmd[cur]))
			end_idx = get_end_index(cmd + cur, -1);
		else
			end_idx = get_end_index(cmd + cur, get_end_arg(cmd + cur, 0));
		if (!end_idx)
			return (lst_clear(args));
		arg = ft_strldup(cmd + cur, end_idx);
		if (!arg)
			return (lst_clear(args));
		if (!lst_append(args, arg))
			return (lst_clear(args));
		cur += ft_strlen(arg) - 1;
	}
	return (1);
}
