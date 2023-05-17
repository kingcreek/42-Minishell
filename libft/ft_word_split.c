/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:57:39 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 03:57:41 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_not_delimiter(char const *str,
					int (*is_delimiter)(char));
static size_t	count_words(char const *str, int (*is_delimiter)(char));
static char		*replace_quoted_delimiter(char const *str,
					int (*is_delimiter)(char));
static char		**split_on_delimiter(char const *str,
					int (*is_delimiter)(char));

char	**ft_word_split(char const *str, int (*is_delimiter)(char))
{
	char	**dest;
	char	*aux;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	aux = replace_quoted_delimiter(str, is_delimiter);
	dest = split_on_delimiter(aux, is_delimiter);
	free(aux);
	if (!dest)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		j = 0;
		while (dest[i][j])
		{
			if (is_delimiter(-dest[i][j]))
				dest[i][j] = -dest[i][j];
			j++;
		}
		i++;
	}
	return (dest);
}

static char	**split_on_delimiter(char const *str, int (*is_delimiter)(char))
{
	char	**dest;
	size_t	i;
	size_t	j;

	dest = malloc((count_words(str, is_delimiter) + 1) * sizeof (char *));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (is_delimiter(str[i]) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		dest[j] = ft_substr(str, i, count_not_delimiter(str + i, is_delimiter));
		if (!dest[j])
			ft_free_matrix((void *)(&dest), j);
		i += count_not_delimiter(str + i, is_delimiter);
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

static size_t	count_not_delimiter(char const *str, int (*is_delimiter)(char))
{
	size_t	i;

	if (!*str)
		return (0);
	i = 0;
	while (str[i] != '\0' && !is_delimiter(str[i]))
		i++;
	return (i);
}

static size_t	count_words(char const *str, int (*is_delimiter)(char))
{
	size_t	word_count;
	size_t	i;

	if (*str == '\0')
		return (0);
	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != is_delimiter(str[i])
			&& (str[i + 1] == is_delimiter(str[i]) || str[i + 1] == '\0'))
			word_count++;
		i++;
	}
	return (i);
}

static char	*replace_quoted_delimiter(char const *str,
	int (*is_delimiter)(char))
{
	char	*quote_end;
	char	*new_str;
	char	*new_str_start;

	if (!str)
		return (NULL);
	new_str = ft_strdup(str);
	new_str_start = new_str;
	while (*new_str)
	{
		if (*new_str == '\'' || *new_str == '\"')
		{
			quote_end = ft_strchr(new_str + 1, *new_str);
			if (quote_end == NULL)
				break ;
			while (new_str - quote_end != 0)
			{
				if (is_delimiter(*new_str))
					*new_str = -*new_str;
				new_str++;
			}
		}
		new_str++;
	}
	return (new_str_start);
}
