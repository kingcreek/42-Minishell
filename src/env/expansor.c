/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:54:58 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 22:47:02 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_quotes(char *str)
{
	char	first_ch;
	char	last_ch;
	int		len;

	len = strlen(str);
	if (len < 2)
		return (0);
	first_ch = str[0];
	last_ch = str[len - 1];
	return ((first_ch == '\'' && last_ch == '\''));
}

static char	*concat_env(t_mini *mini, char *str, int start, int end)
{
	char	*ret;
	char	*tmp;
	char	*substr_env;
	char	*substr_ini;
	char	*substr_end;

	substr_ini = ft_substr(str, 0, start - 1);
	substr_end = ft_substr(str, end, ft_strlen(str) - end);
	substr_env = ft_substr(str, start, end - start);
	tmp = get_env_val(mini, substr_env, mini->last_exit_status);
	ret = ft_calloc(1, (ft_strlen(substr_ini) + ft_strlen(tmp) + \
			ft_strlen(substr_end) + 1) * sizeof(char));
	ret = ft_strcat(ret, substr_ini);
	ret = ft_strcat(ret, tmp);
	ret = ft_strcat(ret, substr_end);
	free(tmp);
	free(substr_env);
	free(substr_ini);
	free(substr_end);
	return (ret);
}

char	*str_to_env(char *str, t_mini *mini)
{
	int		pos;
	int		start;
	int		end;

	pos = 0;
	start = 0;
	end = 0;
	while (str[pos])
	{
		if (str[pos] == '$')
		{
			start = pos + 1;
			while (str[pos] != ' ' && str[pos] != '\0' && str[pos] != '"')
			{
				end = pos + 1;
				pos++;
			}
			return (concat_env(mini, str, start, end));
		}
		pos++;
	}
	return ("");
}

void	expand_env(char **cmds, t_mini *mini)
{
	int		pos;
	char	*newvar;

	pos = 0;
	while (cmds[pos])
	{
		if (!in_quotes(cmds[pos]) && ft_strchr(cmds[pos], '$'))
		{
			newvar = str_to_env(cmds[pos], mini);
			free(cmds[pos]);
			cmds[pos] = newvar;
		}
		pos++;
	}
}
