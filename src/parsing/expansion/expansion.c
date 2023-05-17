/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:13 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:13:11 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*substitute(char *str, size_t sub_start, size_t sub_end, char *sub)
{
	size_t	i;
	char	*joined;
	char	*start_p;
	char	*end_p;

	if (!str || !sub)
		return (NULL);
	start_p = str + sub_start;
	end_p = str + sub_end;
	joined = malloc(ft_strlen(str) - (end_p - start_p) + ft_strlen(sub) + 1);
	if (!joined)
		return (NULL);
	i = 0;
	while (*str && str != start_p)
		joined[i++] = *(str++);
	while (*sub)
		joined[i++] = *(sub++);
	str = end_p;
	while (*str)
		joined[i++] = *(str++);
	joined[i] = '\0';
	return (joined);
}

static char	*expand_tilde(char *str, char *tilde_pointer)
{
	char	*exp;
	char	*path;
	t_var	*home_folder;

	home_folder = var_lst_find_var("HOME", *g_env);
	if (home_folder)
		path = home_folder->value;
	else
		path = getenv("HOME");
	exp = substitute(str, tilde_pointer - str,
			tilde_pointer - str + 1, path);
	free(str);
	return (exp);
}

static char	*expand_var(char *str, char *exp_start, char *var_name)
{
	t_var	*var;
	char	*var_value;
	char	*exp;

	var_value = NULL;
	if (!var_name)
		return (str);
	var = var_lst_find_var(var_name, *g_env);
	if (var && var->value)
		var_value = ft_strdup(var->value);
	else
		var_value = ft_strdup("");
	exp = substitute(str, exp_start - str,
			exp_start - str + ft_strlen(var_name) + 1, var_value);
	free(var_value);
	free(str);
	return (exp);
}

static t_bool	is_expansible_tilde(char *str, size_t tilde_index,
	t_bool is_assignment)
{
	if (!(is_word_start(str, tilde_index)
			|| (is_assignment && str[tilde_index - 1] == ':')))
		return (FALSE);
	if (ft_isspace(str[tilde_index + 1]) || str[tilde_index + 1] == '\0'
		|| str[tilde_index + 1] == ':' || str[tilde_index + 1] == '/')
		return (TRUE);
	return (FALSE);
}

void	find_var_and_expand(char **str, t_bool is_assignment)
{
	char	*var_name;
	size_t	inx;

	inx = 0;
	while ((*str)[inx])
	{
		if ((*str)[inx] == '\'' && !is_within_quotes(*str, inx))
			quit_quote(*str, &inx);
		if ((*str)[inx] == '~' && !is_within_quotes(*str, inx)
			&& is_expansible_tilde(*str, inx, is_assignment))
			*str = expand_tilde(*str, *str + inx);
		if ((*str)[inx] == '$')
		{
			var_name = get_var_name(*str + inx + 1);
			*str = expand_var(*str, *str + inx, var_name);
			if (!var_name)
				inx++;
			free(var_name);
		}
		else
			inx++;
	}
}
