/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:49 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 06:13:32 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_unquoted_pipe(char *str)
{
	size_t	inx;

	inx = 0;
	while (str && str[inx])
	{
		if (str[inx] == '\"' || str[inx] == '\'')
			quit_quote(str, &inx);
		if (str[inx] == '|')
			return (str + inx);
		inx++;
	}
	return (NULL);
}

static t_bool	has_unclosed_quotes(char *str)
{
	size_t	simple_quote_count;
	size_t	double_quote_count;
	size_t	i;

	simple_quote_count = 0;
	double_quote_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && simple_quote_count % 2 == 0)
			double_quote_count++;
		if (str[i] == '\'' && double_quote_count % 2 == 0)
			simple_quote_count++;
		i++;
	}
	if (simple_quote_count % 2 == 1 || double_quote_count % 2 == 1)
	{
		quotes_error();
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	has_pipe_syntax_error(char *usr_in)
{
	char	**words;
	char	*pipe_location;
	size_t	inx;

	words = ft_word_split(usr_in, ft_isspace);
	inx = 0;
	while (words && words[inx])
	{
		pipe_location = get_unquoted_pipe(words[inx]);
		if ((pipe_location && pipe_location == words[0])
			|| (pipe_location && pipe_location[1] == '|')
			|| (pipe_location && pipe_location[1] == '\0' && !words[inx + 1])
			|| (pipe_location && pipe_location[1] == '\0'
				&& get_unquoted_pipe(words[inx + 1])
				&& get_unquoted_pipe(words[inx + 1]) == words[inx + 1]))
		{
			pipe_syntax_error();
			ft_free_char_matrix(&words);
			return (TRUE);
		}
		inx++;
	}
	if (words)
		ft_free_char_matrix(&words);
	return (FALSE);
}

t_pipe	*pipe_parse(char *usr_in, t_shell *st_shell)
{
	t_pipe	*lst;
	size_t	inx;

	if (is_empty_str(usr_in) || has_unclosed_quotes(usr_in)
		|| has_pipe_syntax_error(usr_in))
		return (NULL);
	lst = NULL;
	inx = 0;
	while (usr_in[inx])
	{
		if (usr_in[inx] == '\"' || usr_in[inx] == '\'')
			quit_quote(usr_in, &inx);
		if (usr_in[inx] == '|')
		{
			pipe_lst_add_back(&lst, pipe_lst_new(ft_substr(usr_in, 0, inx)));
			if (usr_in[inx + 1] != '\0')
				usr_in += inx + 1;
			inx = 0;
			continue ;
		}
		inx++;
	}
	pipe_lst_add_back(&lst, pipe_lst_new(ft_substr(usr_in, 0, inx)));
	st_shell->lst_size = pipe_lst_size(lst);
	return (lst);
}

t_bool	is_empty_str(char *usr_in)
{
	char	*aux;

	if (!usr_in || !*usr_in)
		return (TRUE);
	aux = ft_strtrim(usr_in, WHITE_SPACE_CHARS);
	if (!aux)
		return (TRUE);
	if (!*aux)
	{
		free(aux);
		return (TRUE);
	}
	free(aux);
	return (FALSE);
}
