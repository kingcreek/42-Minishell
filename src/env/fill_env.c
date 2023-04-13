/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:23:34 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/11 16:50:00 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Agrega una nueva variable de entorno a la estructura t_mini
int	add_env_var(t_mini *mini, char *key, char *val)
{
	t_envs	*new;
	t_envs	*curr;

	new = malloc(sizeof(t_envs));
	if (!new)
		return (-1);
	new->key = key;
	new->val = val;
	new->next = NULL;
	if (!mini->envs)
		mini->envs = new;
	else
	{
		curr = mini->envs;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	free(key);
	return (0);
}


// Agrega todas las variables de entorno a la estructura t_mini
int	load_env_vars(t_mini *mini, char **envp)
{
	int		i;
	char	*key;
	char	*val;

	i = 0;
	while (envp[i])
	{
		key = ft_strchr(envp[i], '=');
		if (!key)
			key = envp[i];
		else
			key = ft_substr(envp[i], 0, key - envp[i]);
		val = ft_strchr(envp[i], '=') + 1;
		if (!val)
			val = "";
		if (add_env_var(mini, key, val) == -1)
			return (-1);
		i++;
	}
	return (0);
}

// Retorna el valor de una variable de entorno dado su nombre (key)
char	*get_env_val(t_mini *mini, char *key)
{
	t_envs	*env_var;

	env_var = mini->envs;
	while (env_var)
	{
		if (ft_strcmp(env_var->key, key) == 0)
			return (env_var->val);
		env_var = env_var->next;
	}
	return (NULL);
}

// Modifica el valor de una variable de entorno dado su nombre (key)
int	set_env_var(t_mini *mini, char *key, char *new_val)
{
	t_envs	*env_var;

	env_var = mini->envs;
	while (env_var)
	{
		if (ft_strcmp(env_var->key, key) == 0)
		{
			free(env_var->val);
			env_var->val = ft_strdup(new_val);
			if (!env_var->val)
				return (-1);
			return (0);
		}
		env_var = env_var->next;
	}
	return (add_env_var(mini, ft_strdup(key), ft_strdup(new_val)));
}

// Libera la memoria ocupada por la estructura t_mini
void	free_mini(t_mini *mini)
{
	t_envs	*env_var;
	t_envs	*next;

	env_var = mini->envs;
	while (env_var)
	{
		free(env_var->key);
		free(env_var->val);
		next = env_var->next;
		free(env_var);
		env_var = next;
	}
	free(mini);
}
