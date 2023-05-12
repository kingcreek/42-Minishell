/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:19:28 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/12 16:21:19 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **cmd, t_mini *mini)
{
	char	*path;
	int		ret;

	if (!cmd[1])
		path = get_env_val(mini, "HOME", mini->last_exit_status);
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		path = get_env_val(mini, "OLDPWD", mini->last_exit_status);//ft_get_env_var("OLDPWD", mini->envs);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return ;
		}
	}
	else
		path = cmd[1];
	ret = chdir(path);
	if (ret != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
	{
		set_env_var(mini, "OLDPWD", get_env_val(mini, "PWD", mini->last_exit_status)/*ft_get_env_var("PWD", mini->envs)*/);
		set_env_var(mini, "PWD", getcwd(NULL, 0));
	}
}