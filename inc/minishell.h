/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:14:01 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/13 14:18:09 by imurugar         ###   ########.fr       */
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define UNKNOWN_COMMAND 127

typedef struct s_command
{
	char	*cmd;
	void	*next;
	void	*prev;
}			t_command;

typedef struct s_envs
{
	char	*key;
	char	*val;
	void	*next;
}			t_envs;

typedef struct s_cmdlst
{
	char			*command;
	char			**args;
	char			**infiles;
	//t_outlst		*outfiles;
	char			**heredocs;
	int				todo_next;
	struct s_cmdlst	*next;
}	t_cmdlst;

typedef struct s_mini
{
	t_envs		*envs;
	t_command	*cmds;
	int			exit_status;
}			t_mini;

void	start_handles(void);
int		load_env_vars(t_mini *mini, char **envp);
//void	set_envs(char **environ, t_envs **envs);

/* ENV */
char	*get_env_val(t_mini *mini, char *key);

/* PARSER */
int		check_quotes(char *command);

/* HELPERS */
void	free_2d_str(char **lst);
int		free_t_mini(t_mini *mini);
int		print_error(int error_code, char *content);

#endif