/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:29:30 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/11 14:11:43 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	*pwd;
	
	pwd = get_env_val(mini, "PWD", mini->last_exit_status);
	if (pwd)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		mini->cmd_exit_status = 0;
		free(pwd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("\033[91m%s\033[0m\n",
			"minishell: pwd does not work if PWD is unset");
		mini->cmd_exit_status = 1;
		exit(EXIT_FAILURE);
	}
}
