/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:14:01 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/12 15:46:43 by imurugar         ###   ########.fr       */
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
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

/* ERROR MSG */
# define QUOTES	"parse error, quotes are never closed"
# define NEAR	"parse error, near "
# define ENDS	"the command cannot end with "

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

/* OUTPUT FILES */
# define WRITE 0
# define APPEND 1

# define UNKNOWN_COMMAND 127

extern pid_t		g_pid;

/* Get all ENV and store here like a HasMap<key, Value> */
typedef struct s_envs
{
	char	*allenv;
	char	*key;
	char	*val;
	void	*next;
}			t_envs;

/* For each cmd, store output files with action ">", ">>" */
typedef struct s_o_file
{
	char			*filename;
	int				action;
	struct s_o_file	*next;
}	t_o_file;

/* All comands stored here */
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

/* Execution args */
typedef struct s_exec
{
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	char	*redirect_file_path;
	char	*right_path;
}	t_exec;

typedef struct s_exec_loop
{
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		fdpipe[2];
	char	*redirect_file_path;
	char	*right_path;
}	t_exec_loop;

/* Main struct to store all data info */
typedef struct s_mini
{
	t_exec		*exec;
	t_envs		*envs;
	char		*exec_path;
	char		*path_env;
	char		**path_tab;
	char		*tmpfile;
	int			cmd_exit_status;
	int			last_exit_status;
	t_exec_loop	*exec_loop;
}			t_mini;

/* SIGNAL */
void	start_handles(void);
int		load_env_vars(t_mini *mini, char **envp);

/* ENV */

//Fill env
char	*get_env_val(t_mini *mini, char *key, int last_exit);
int		set_env_var(t_mini *mini, char *key, char *new_val);
char	**get_all_env(t_mini *mini);

//Expansor
void	expand_env(char **cmds, t_mini *mini);

/* PARSER */

//Checker
int		check_quotes(char *command);
int		check_specials(t_list *list);
int		get_arg_type(char *str);
int		is_sep(char *str);

//Parser
int		split_args(t_list **args, char *cmd);
int		get_end_index(char *str, int end);
int		get_end_arg(char *str, int quote_idx);
int		get_end_queotes(char *str, int end);

//List
int		lst_append(t_list **lst, char *str);
int		strarr_append(char ***array, char *str);
int		cmdlist_len(t_cmdlst *lst);

//Cmd
int		fill_cmd_list(t_cmdlst **command_list, t_list *args);

//Outfiles
int		append_out_args(t_list **args, char *op, t_o_file **out);

/* HELPERS */

//Free
int		strarr_free(char **arr);
int		free_t_mini(t_mini *mini, int exit);
int		lst_clear(t_list **lst);
int		cmd_clear(t_cmdlst **lst);
int		free_array_n(char **array, int n);
void	free_paths(t_mini *mini);

//Error
int		print_error(int error_code, char *content);

//Helper
int		is_simbol(char c);

//List
int		strarr_len(char **array);


//Utils
int		index_new_line(char *str);
int		index_of(char *str, char *search, int len);
int		outlst_len(t_o_file *lst);
int		contains_only(char *str, char c);

/* EXECUTE */

//Execute
void	execute(t_cmdlst *lst, t_mini *mini);

//Execute Utils
int		is_exit(t_cmdlst *lst);

/* BUILT IN*/
//echo
int		ft_echo(char **s, t_mini *mini);
//PWD
int		ft_pwd(t_mini *mini);
//Exit
void	ft_exit(t_mini *mem, t_cmdlst *lst);
//Env
void	ft_env(t_mini *mini);
//Unset
int		ft_unset(t_mini *mini, char **args);
//Export
int		ft_export(t_mini *mini, char **args);
//Cd
void	ft_cd(char **cmd, t_mini *mini);

#endif