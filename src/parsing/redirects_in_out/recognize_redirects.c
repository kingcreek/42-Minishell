/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognize_redirects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:07 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/16 16:54:08 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_dir(char *file)
{
	DIR	*dir;

	dir = opendir(file);
	if (dir)
	{
		closedir(dir);
		return (TRUE);
	}
	return (FALSE);
}

t_error	check_file_access(char **file, t_tokens token, t_shell *st_shell)
{
	find_var_and_expand(file, FALSE);
	st_shell->error_locale = ft_strdup(*file);
	if (is_dir(*file))
		return (IS_DIR);
	if (token == INFILE)
	{
		if (access(*file, F_OK) != 0)
			return (NO_DIR);
		if (access(*file, R_OK) != 0)
			return (DENI_PERMI);
		st_shell->infile = open(*file, O_RDONLY);
	}
	else if (token == OUTFILE || token == APPEND)
	{
		if (token == APPEND)
			st_shell->outfile = open(*file, O_APPEND | O_RDWR | O_CREAT, 0644);
		else
			st_shell->outfile = open(*file, O_TRUNC | O_RDWR | O_CREAT, 0644);
		if (st_shell->outfile == -1)
			return (DENI_PERMI);
	}
	free(st_shell->error_locale);
	return (SUCCESS);
}

void	check_status(t_shell *st_shell)
{
	if (st_shell->file_stat == NO_DIR)
		generic_error(1, st_shell->error_locale, ERROR_FILE_DIR);
	else if (st_shell->file_stat == DENI_PERMI)
		generic_error(1, st_shell->error_locale, ERROR_PERMI);
	else if (st_shell->file_stat == IS_DIR)
		generic_error(1, "-", "Is a directory");
	free(st_shell->error_locale);
}

t_bool	set_redirect(t_pipe *pipe_lst, t_shell *st_shell, size_t inx)
{
	t_tokens	token;
	int			start_inx;

	start_inx = inx;
	token = get_token(pipe_lst->str, &inx);
	inx++;
	if (ft_isspace(pipe_lst->str[inx]) != 0)
		while (ft_isspace(pipe_lst->str[inx]) != 0)
			inx++;
	if (error_syntax(&pipe_lst->str[inx]) == FALSE)
		return (FALSE);
	if (file_name(&pipe_lst->str[inx], &inx, token, st_shell) == FALSE)
		return (FALSE);
	cut_str(pipe_lst, start_inx, inx);
	return (TRUE);
}

int	recognize_redirect(t_pipe *pipe_lst, t_shell *st_shell)
{
	size_t	inx;

	inx = 0;
	while (pipe_lst->str[inx])
	{
		if (pipe_lst->str[inx] == '\'' || pipe_lst->str[inx] == '\"')
			quit_quote(pipe_lst->str, &inx);
		else if (ft_strchr("<>", pipe_lst->str[inx]))
		{
			if (set_redirect(pipe_lst, st_shell, inx) == FALSE)
				return (-1);
			else
				inx = -1;
		}
		inx++;
	}
	if (st_shell->file_stat != SUCCESS)
	{
		check_status(st_shell);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
