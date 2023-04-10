/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:23:34 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/10 16:30:49 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_envs	*new_env(char *key, char *val)
{
	t_envs	*env;

	env = malloc(sizeof(t_envs));
	if (env == NULL)
		exit(1);
	env->key = ft_strdup(key);
	env->val = ft_strdup(val);
	env->next = NULL;
	return (env);
}

static void	add_env(t_envs **envs, t_envs *env)
{
	t_envs	*last_env;

	if (*envs == NULL)
	{
		*envs = env;
		return ;
	}
	last_env = *envs;
	while (last_env->next != NULL)
		last_env = last_env->next;
	last_env->next = env;
}

void	set_envs(char **environ, t_envs **envs)
{
	char	*key;
	char	*val;
	int		i;

	if (environ == NULL || envs == NULL)
		return ;
	i = 0;
	while (environ[i] != NULL)
	{
		key = environ[i];
		val = ft_strchr(key, '=');
		if (val == NULL)
		{
			i++;
			continue ;
		}
		*val = '\0';
		val++;
		printf("%s\n", key);
		add_env(envs, new_env(key, val));
		i++;
	}
}
