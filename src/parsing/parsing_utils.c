/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:46 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 05:08:42 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_quote(char *str, size_t *inx)
{
	char	quote;

	quote = str[*inx];
	*inx = *inx + 1;
	while (str[*inx])
	{
		if (str[*inx] == quote)
			break ;
		*inx += 1;
	}
}

t_bool	is_word_start(char *str, size_t index)
{
	if (index == 0 || ft_isspace(str[index - 1]))
		return (TRUE);
	return (FALSE);
}

t_bool	is_within_quotes(char *str, size_t index)
{
	size_t	simple_quote_count;
	size_t	double_quote_count;
	size_t	i;

	simple_quote_count = 0;
	double_quote_count = 0;
	i = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '"' && simple_quote_count % 2 == 0)
			double_quote_count++;
		if (str[i] == '\'' && double_quote_count % 2 == 0)
			simple_quote_count++;
		i++;
	}
	if (simple_quote_count % 2 == 1 || double_quote_count % 2 == 1)
		return (TRUE);
	return (FALSE);
}

static size_t	count_removable_quotes_in_word(char *str, size_t word_end)
{
	size_t	removable_quote_count;
	size_t	simple_quote_count;
	size_t	double_quote_count;
	size_t	index;

	index = 0;
	removable_quote_count = 0;
	simple_quote_count = 0;
	double_quote_count = 0;
	while (str[index] && index < word_end)
	{
		if (str[index] == '"' && simple_quote_count % 2 == 0)
		{
			double_quote_count++;
			removable_quote_count++;
		}
		if (str[index] == '\'' && double_quote_count % 2 == 0)
		{
			simple_quote_count++;
			removable_quote_count++;
		}
		index++;
	}
	return (removable_quote_count);
}

char	*remove_quotes_from_word(char *str, size_t word_end)
{
	size_t	aux;
	size_t	index;
	size_t	simple_quote_count;
	size_t	double_quote_count;
	char	*res;

	index = 0;
	aux = 0;
	simple_quote_count = 0;
	double_quote_count = 0;
	res = ft_calloc(ft_strlen(str) + 1
			- count_removable_quotes_in_word(str, word_end), sizeof(char));
	while (str[index] && index < word_end)
	{
		if (str[index] == '"' && simple_quote_count % 2 == 0)
			double_quote_count++;
		else if (str[index] == '\'' && double_quote_count % 2 == 0)
			simple_quote_count++;
		else
			res[aux++] = str[index];
		index++;
	}
	return (res);
}
