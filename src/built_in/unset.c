/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:17:34 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/12 14:14:52 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void update_exit_status(t_mini *mini, int not_found)
{
    if (not_found > 0)
        mini->cmd_exit_status += not_found;
}

int delete_env(t_mini *mini, char *key, int *not_found)
{
    t_envs *env;
    t_envs *prev;

	env = mini->envs;
	prev = NULL;
    while (env != NULL)
    {
        if (strcmp(env->key, key) == 0)
        {
            if (prev == NULL)
				mini->envs = env->next;
            else
                prev->next = env->next;
            free(env->key);
            free(env->val);
            free(env);
            return 1;
        }
        prev = env;
        env = env->next;
    }
    return 0;
}

int	ft_unset(t_mini *mini, char **args)
{
    int i = 1;
    int not_found = 0;

    while (args[i] != NULL)
    {
        if (!delete_env(mini, args[i], &not_found))
            not_found++;
        i++;
    }
    update_exit_status(mini, not_found);
	return (1);
}
