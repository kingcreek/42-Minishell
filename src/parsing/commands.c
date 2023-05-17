/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:58 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:13:31 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_args_quote(char **args)
{
	size_t	inx;
	char	*unquoted;

	if (!args)
		return ;
	inx = 0;
	while (args[inx])
	{
		unquoted = remove_quotes_from_word(args[inx], ft_strlen(args[inx]));
		free(args[inx]);
		args[inx] = unquoted;
		inx++;
	}
}

char	**set_cmds_paths(void)
{
	t_var	*path;
	char	*paths;

	path = var_lst_find_var("PATH", *g_env);
	if (!path)
		return (NULL);
	paths = path->value;
	return (ft_split(paths, ':'));
}

t_bool	check_paths(t_shell *st_shell)
{
	char	**cmds_paths;
	char	*tmp;
	int		inx;

	cmds_paths = set_cmds_paths();
	inx = 0;
	while (cmds_paths && cmds_paths[inx])
	{
		tmp = ft_strjoin(cmds_paths[inx], "/");
		st_shell->cmd = ft_strjoin(tmp, st_shell->args[0]);
		free(tmp);
		if (access(st_shell->cmd, X_OK) == 0)
		{
			ft_free_char_matrix(&cmds_paths);
			return (TRUE);
		}
		free(st_shell->cmd);
		inx++;
	}
	cmd_error(st_shell, cmds_paths);
	set_exit_status(127);
	st_shell->exit_status = 127;
	return (FALSE);
}

t_bool	recognizer_cmd(t_pipe *pipe_lst, t_shell *st_shell)
{
	st_shell->args = ft_word_split(pipe_lst->str, ft_isspace);
	remove_args_quote(st_shell->args);
	if (st_shell->args[0][0] == '/' ||
		(st_shell->args[0][0] == '.' && st_shell->args[0][1] == '/'))
	{
		if (access(st_shell->args[0], F_OK) != 0)
		{
			free_args_error(st_shell, ERROR_FILE_DIR);
			st_shell->exit_status = 127;
			return (FALSE);
		}
		if (access(st_shell->args[0], X_OK) == 0)
		{
			st_shell->cmd = ft_strdup(st_shell->args[0]);
			return (TRUE);
		}
		else
		{
			free_args_error(st_shell, ERROR_PERMI);
			st_shell->exit_status = 126;
			return (FALSE);
		}
	}
	return (check_paths(st_shell));
}
