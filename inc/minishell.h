/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:14:01 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/16 16:30:11 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* STDR output */

# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* Action types */
# define PIPE 1
# define AND 2
# define OR 3
# define CONTINUE 4
# define END 0

/* COLORS */
# define COLOR_RED		"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_YELLOW	"\033[33m"
# define COLOR_BLUE		"\033[34m"
# define COLOR_MAGENTA	"\033[35m"
# define COLOR_CYAN		"\033[36m"
# define COLOR_RESET	"\033[0m"

# define UNKNOWN_COMMAND 127

/* We split the argv command and save each cmd */
typedef struct s_command
{
	char	*cmd;
	void	*next;
	void	*prev;
}			t_command;

/* Get all ENV and store here like a HasMap<key, Value> */
typedef struct s_envs
{
	char	*key;
	char	*val;
	void	*next;
}			t_envs;

/* For each cmd, store output files with action ">", ">>" */
typedef struct s_o_file
{
	char			*filename;
	int				action;
	struct s_outlst	*next;
}	t_o_file;

/* All comands stored here to do pipex! */
typedef struct s_cmdlst
{
	char			*command;
	char			**args;
	char			**infiles;
	t_o_file		*outfiles;
	char			**heredocs;
	int				todo_next;
	struct s_cmdlst	*next;
}	t_cmdlst;

/* Main struct to store all data info */
typedef struct s_mini
{
	t_envs		*envs;
	t_command	*cmds;
	char		**path;
	int			exit_status;
}			t_mini;

/* SIGNAL */
void	start_handles(void);
int		load_env_vars(t_mini *mini, char **envp);

/* ENV */
char	*get_env_val(t_mini *mini, char *key);

/* PARSER */
//Checker
int		check_quotes(char *command);
int		check_specials(t_list *list);
int		get_arg_type(char *str);
//Parser
int		split_args(t_list **args, char *cmd);
int		get_end_index(char *str, int end);
int		get_end_arg(char *str, int quote_idx);
int		get_end_queotes(char *str, int end);
//List
int		lst_append(t_list **lst, char *str);
//Cmd
int		fill_cmd_list(t_cmdlst **command_list, t_list *args);

/* HELPERS */
//Free
int		strarr_free(char **arr);
int		free_t_mini(t_mini *mini);
int		lst_clear(t_list **lst);
//Error
int		print_error(int error_code, char *content);
//Helper
int		is_simbol(char c);
//Utils
int		index_new_line(char *str);
int		index_of(char *str, char *search, int len);

#endif