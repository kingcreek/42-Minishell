/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:03 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/16 16:54:05 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_str_size(t_pipe *pipe_lst, int start_inx, int end_inx)
{
	int	inx;
	int	new_str_size;

	inx = 0;
	new_str_size = 0;
	while (pipe_lst->str[inx])
	{
		if (inx < start_inx || inx > end_inx)
			new_str_size++;
		inx++;
	}
	return (new_str_size);
}

void	cut_str(t_pipe *pipe_lst, int start_inx, int end_inx)
{
	int		new_str_size;
	int		new_str_inx;
	int		inx;
	char	*new_str;

	new_str_size = count_str_size(pipe_lst, start_inx, end_inx);
	new_str = ft_calloc(sizeof(char), new_str_size + 1);
	inx = 0;
	new_str_inx = 0;
	while (pipe_lst->str[inx] != 0 && new_str_size != 0)
	{
		if (inx < start_inx || inx > end_inx)
		{
			new_str[new_str_inx] = pipe_lst->str[inx];
			new_str_inx++;
		}
		inx++;
	}
	free(pipe_lst->str);
	pipe_lst->str = new_str;
}

t_bool	file_name(char *file, size_t *str_inx, t_tokens tk, t_shell *shell)
{
	size_t	file_inx;
	char	*unquoted;

	file_inx = 0;
	while (ft_isprint(file[file_inx]) && file[file_inx] != '\0')
	{
		if (file[file_inx] == '\'' || file[file_inx] == '\"')
			quit_quote(file, &file_inx);
		if (ft_strchr("<> ", file[file_inx]) != NULL)
			break ;
		file_inx++;
	}
	unquoted = remove_quotes_from_word(file, file_inx);
	*str_inx += file_inx;
	if (tk == HEREDOC)
	{
		heredoc_sig_setup();
		if (here_doc(unquoted, shell) == FALSE)
			return (free_return(unquoted));
		sig_setup();
	}
	else if (tk != HEREDOC && shell->file_stat == 0)
		shell->file_stat = check_file_access(&unquoted, tk, shell);
	free(unquoted);
	return (TRUE);
}

t_tokens	get_token(char *str, size_t *inx)
{
	if (str[*inx] == '>' && str[*inx + 1] == '>')
	{
		(*inx)++;
		return (APPEND);
	}
	else if (str[*inx] == '<' && str[*inx + 1] == '<')
	{
		(*inx)++;
		return (HEREDOC);
	}
	else if (str[*inx] == '<')
		return (INFILE);
	else if (str[*inx] == '>')
		return (OUTFILE);
	return (NOT_REDIR);
}
