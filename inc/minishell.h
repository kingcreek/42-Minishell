/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:14:01 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/10 15:41:11 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERR_MALLOC 0
# define ERR_CMD 	1

typedef struct s_command
{
	char	*cmd;
	void	*next;	
}			t_command;

typedef struct s_envs
{
	char	*key;
	char	*val;
	void	*next;	
}			t_envs;

typedef struct s_mini
{
	t_envs	*envs;	
}			t_mini;

void	start_handles(void);
void	set_envs(char **environ, t_envs **envs);

#endif