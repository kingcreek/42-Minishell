/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 03:23:48 by imurugar          #+#    #+#             */
/*   Updated: 2023/07/05 20:56:24 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>

# define LULUSHELL			 "👾 Minishell 👾 > "
# define BUILDS_COUNT		 7
# define BUILTIN_MISUSE_CODE 2
# define SYNTAX_ERROR		 "syntax error near unexpected token "
# define EOF_ERROR "warning: here-document delimited by end-of-file (wanted `"
# define MINISHELL_ERROR	 "Minishell: "
# define ERROR_FILE_DIR		 "No such file or directory"
# define ERROR_PERMI		 "Permission denied"

# define WHITE_SPACE_CHARS " \f\n\r\t\v"

typedef struct s_builtin
{
	char	*name;
	void	(*func)();
}	t_builtin;

typedef enum e_error
{
	SUCCESS,
	NO_DIR,
	DENI_PERMI,
	IS_DIR
}	t_error;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_shell
{
	char		*cmd;
	char		**args;
	int			pipe[2];
	int			lst_inx;
	int			infile;
	int			outfile;
	int			lst_size;
	int			exit_status;
	char		*error_locale;
	t_error		file_stat;
}	t_shell;

typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}	t_var;

typedef struct s_pipe
{
	char			*str;
	struct s_pipe	*next;
}	t_pipe;

typedef enum e_tokens
{
	INFILE,
	OUTFILE,
	APPEND,
	HEREDOC,
	NOT_REDIR
}	t_tokens;

void		ft_echo(char *usr_in, int write_fd);
void		ft_env(int write_fd);
void		ft_pwd(int write_fd);
void		ft_cd(char *usr_in);
void		ft_exit(char *usr_in, t_pipe *pipe_lst, t_builtin *builds,
				t_bool print);
void		ft_export(char *usr_in, int write_fd);
t_var		*sort_variables(const t_var *head);
void		ft_unset(char *usr_in);

// commands.c
t_bool		recognizer_cmd(t_pipe *pipe_lst, t_shell *st_shell);
void		fork_exec(t_shell *st_shell, t_pipe *pipe_lst);

// build_ins.c
t_bool		is_builds(t_pipe *pipe_lst, t_shell *st_shell);
t_builtin	*init_builds(void);
int			hash_search(const char *key, t_builtin *builds);

// parsing_parse.c
t_pipe		*pipe_parse(char *usr_in, t_shell *s_shell);
t_bool		is_empty_str(char *usr_in);

// parsing.c
void		parsing(char *std_in, t_shell *st_shell);
char		*find_var_assignment(char *str);

// expansion.c
void		find_var_and_expand(char **usr_in, t_bool is_assignment);

// parsing_utils.c
void		quit_quote(char *str, size_t *inx);
t_bool		is_word_start(char *str, size_t index);
t_bool		is_within_quotes(char *str, size_t index);
char		*remove_quotes_from_word(char *str, size_t word_end);

// var_utils.c
t_bool		is_valid_varname(char *str);
t_bool		is_valid_varname_char(char c);
char		*get_var_name(char *str);
t_var		*get_var_from_assignment(char *str);

// set_in_outs.c
void		set_in_out(t_shell *st_shell);
t_bool		set_redirect(t_pipe *pipe_lst, t_shell *st_shell, size_t inx);
int			recognize_redirect(t_pipe *tk_lst, t_shell *shell);
t_error		check_file_access(char **file, t_tokens token, t_shell *st_shell);

// redirect_utils.c
void		cut_str(t_pipe *pipe_lst, int start_inx, int end_inx);
t_tokens	get_token(char *str, size_t *inx);
t_bool		file_name(char *file, size_t *str_inx, t_tokens tk, t_shell *shell);

// heredoc.c
t_bool		here_doc(char *delimiter, t_shell *shell);

//pipelst
t_pipe		*pipe_lst_new(char *str_in);
void		pipe_lst_add_back(t_pipe **lst, t_pipe *new);
void		pipe_lst_add_front(t_pipe **lst, t_pipe *new);
void		pipe_lst_delete_node(t_pipe *node);
void		pipe_lst_clear(t_pipe **lst);
int			pipe_lst_size(t_pipe *lst);

// lst_add.c
t_var		*var_lst_new(char *name, char *value);
void		var_lst_add_back(t_var **lst, t_var *new);
void		var_lst_add_front(t_var **lst, t_var *new);
void		var_lst_add_var(t_var **lst, t_var *new);

// lst_del.c
void		var_lst_clear(t_var **lst);
void		var_lst_delete_node(t_var *node);
void		var_lst_delete_var(t_var **lst, char *name);

// lst_get.c
size_t		var_lst_size(t_var *lst);
t_var		*var_lst_find_var(char *name, t_var *lst);

int			get_exit_status(void);

void		init(char **envp);
void		get_comman(char *usr_in, t_shell *comman);
void		exec(t_shell *st_shell, char **envp, t_pipe *pipe_lst);
void		set_exit_status(int exit_status);
t_var		**set_node(void);

// signal_setup.c
void		sig_setup(void);
void		child_sig_setup(void);
void		heredoc_sig_setup(void);

// signal_handler.c
void		signal_handler(int signal);
void		child_signal_handler(int signal);
void		heredoc_signal_handler(int signal);

// frees_and_closes.c
void		close_fds(t_shell *st_shell);
void		close_pipes(t_shell *st_shell);
void		cmd_error(t_shell *st_shell, char **paths);
void		free_args_error(t_shell *st_shell, char *message);
t_bool		free_return(char *str_free);

// error.c
t_bool		generic_error(int exit_status, char *locale, char *message);
void		pipe_syntax_error(void);
int			error_syntax(char *str);
void		quotes_error(void);

extern t_var	**g_env;

#endif
