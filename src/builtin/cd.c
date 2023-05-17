/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:52:55 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:07:45 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_directory(char *path)
{
	t_var	*home_dir;
	int		status;
	char	*pwd;

	if (path == NULL)
	{
		home_dir = var_lst_find_var("HOME", *g_env);
		if (!home_dir)
		{
			set_exit_status(EXIT_FAILURE);
			ft_putendl_fd("cd: HOME not set", 2);
			return ;
		}
		path = home_dir->value;
	}
	status = chdir(path);
	if (status == -1)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		set_exit_status(EXIT_FAILURE);
		return (perror(NULL));
	}
	pwd = getcwd(NULL, 0);
	var_lst_add_var(g_env, var_lst_new(ft_strdup("PWD"), pwd));
}

static t_bool	is_valid_input(char **words)
{
	if (!words)
		return (FALSE);
	if (words[1] && words[2])
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (FALSE);
	}
	return (TRUE);
}

void	ft_cd(char *usr_in)
{
	char	**words;
	char	*unquoted_path;
	char	*old_pwd;

	set_exit_status(EXIT_SUCCESS);
	words = ft_word_split(usr_in, ft_isspace);
	if (!is_valid_input(words))
	{
		ft_free_char_matrix(&words);
		return (set_exit_status(EXIT_FAILURE));
	}
	unquoted_path = NULL;
	if (words[1])
		unquoted_path = remove_quotes_from_word(words[1], ft_strlen(words[1]));
	old_pwd = getcwd(NULL, 0);
	var_lst_add_var(g_env, var_lst_new(ft_strdup("OLDPWD"), old_pwd));
	change_directory(unquoted_path);
	free(unquoted_path);
	ft_free_char_matrix(&words);
	return ;
}
