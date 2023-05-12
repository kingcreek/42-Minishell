/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:18:40 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/12 16:27:51 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_key(char *s)
{
	int	i;

	if (!s || !(*s) || !ft_isalpha(*s) && *s != '_')
		return (0);
	i = 1;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (s[i] == '=' || !s[i]);
}

char	*get_env_key(char *s)
{
	char	*key;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	key = ft_substr(s, 0, i);
	return (key);
}

char	*get_env_value(char *s)
{
	char	*val;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!s[i])
		return (ft_strdup(""));
	val = ft_strdup(s + i + 1);
	return (val);
}

void	export_var(t_mini *mini, char *key, char *val)
{
	if (set_env_var(mini, key, val) == -1)
	{
		perror("minishell: export");
		mini->cmd_exit_status = 1;
	}
}

int	ft_export(t_mini *mini, char **args)
{
	int		i;
	char	*key;
	char	*val;
	int		status;

	i = 1;
	while (args[i])
	{
		key = ft_strcdup(args[i], '=');
		if (!key)
			return (0);
		val = ft_strcdup_end(args[i], '=');
		if (!val)
			val = ft_strdup("");
		status = set_env_var(mini, key, val);
		free(key);
		if (status == -1)
		{
			mini->cmd_exit_status = 1;
			return (0);
		}
		i++;
	}
	mini->cmd_exit_status = 0;
	return (1);
}