/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:23:34 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 22:02:05 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function adds a new environment variable
 * to a linked list of environment variables in a mini
 * shell program.
 * 
 * @param mini A pointer to a struct containing information
 * about the current state of the shell
 * program.
 * @param key The key parameter is a string that represents
 * the name of the environment variable being
 * added.
 * @param val The "val" parameter in the "add_env_var" function
 * is a string that represents the value
 * of the environment variable being added to the linked list.
 * @param all The `all` parameter is a string that contains the
 * entire environment variable in the
 * format "key=value". It is used to store the original environment
 * variable string in the linked list node for later use.
 * 
 * @return an integer value, which is either 0 or -1.
 */
int	add_env_var(t_mini *mini, char *key, char *val, char *all)
{
	t_envs	*new;
	t_envs	*curr;

	new = malloc(sizeof(t_envs));
	if (!new)
		return (-1);
	new->allenv = all;
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
	//free(key);
	return (0);
}

/**
 * The function loads environment variables from an array
 * of strings and adds them to a data structure in a C program.
 * 
 * @param mini a pointer to a struct containing
 * information about the shell program
 * @param envp The envp parameter is a null-terminated
 * array of strings that represent the environment
 * variables passed to the program.
 * Each string in the array is in the format "key=value".
 * 
 * @return an integer value. If the function successfully
 * adds all environment variables to the mini
 * shell's environment variable list, it returns 0.
 * If there is an error while adding any of the
 * environment variables, it returns -1.
 */
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
		if (add_env_var(mini, key, val, envp[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

/**
 * This function searches for a specific environment
 * variable by its key and returns its value.
 * 
 * @param mini A pointer to a struct of type t_mini,
 * which likely contains information about the
 * current state of a mini shell program.
 * @param key The key is a string representing the name
 * of the environment variable whose value we want
 * to retrieve.
 * 
 * @return The function `get_env_val` returns a pointer
 * to a character (char*) which is the value of
 * the environment variable with the given key.
 * If the key is not found in the linked list of
 * environment variables, the function returns NULL.
 */
char	*get_env_val(t_mini *mini, char *key, int last_exit)
{
	t_envs	*env_var;

	if (key[0] == '?')
		return (ft_itoa(last_exit));
	else if (ft_contains_only(key, '$'))
		return (ft_strdup(key));
	else if (key[0] == '$')
		return (ft_strdup("$"));
	else if (key[0] == '"' || key[1] == '\'')
		return (ft_strdup("$"));
	else if (!ft_isalpha(key[0]))
		return (ft_strdup(""));
	env_var = mini->envs;
	while (env_var)
	{
		if (ft_strcmp(env_var->key, key) == 0)
			return (ft_strdup(env_var->val));
		env_var = env_var->next;
	}
	return (ft_strdup(""));
}

/**
 * The function sets the value of an environment variable
 * or adds a new environment variable if it does
 * not exist.
 * 
 * @param mini a pointer to a struct containing information
 * about the current shell session
 * @param key The key is a string representing the name of
 * the environment variable that needs to be
 * set or updated.
 * @param new_val The new value that we want to set for the environment variable.
 * 
 * @return The function `set_env_var` returns an integer value.
 * It returns 0 if the environment
 * variable with the given key is found and its value
 * is successfully updated with the new value. It
 * returns -1 if there is an error in allocating memory
 * for the new value. If the environment variable
 * with the given key is not found,
 * the function calls `add_env_var` to add a new environment variable
 */
int	set_env_var(t_mini *mini, char *key, char *new_val)
{
	t_envs	*env_var;
	char	*tmp;
	char	*full_env;

	env_var = mini->envs;
	tmp = ft_strjoin(key, "=");
	full_env = ft_strjoin(tmp, new_val);
	free(tmp);
	while (env_var)
	{
		if (ft_strcmp(env_var->key, key) == 0)
		{
			free(env_var->allenv);
			env_var->allenv = full_env;
			free(env_var->val);
			env_var->val = ft_strdup(new_val);
			if (!env_var->val)
				return (-1);
			return (0);
		}
		env_var = env_var->next;
	}
	return (add_env_var(mini, ft_strdup(key), ft_strdup(new_val), ""));
}
