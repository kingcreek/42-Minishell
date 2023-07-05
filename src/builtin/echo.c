/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:52:58 by imurugar          #+#    #+#             */
/*   Updated: 2023/07/05 20:08:06 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	has_n_flag(char **words)
{
	char	*unquoted;
	t_bool	n_flagged;

	if (!words || !words[1])
		return (FALSE);
	unquoted = remove_quotes_from_word(words[1], ft_strlen(words[1]));
	if (ft_strncmp(unquoted, "-n", 3) == 0)
		n_flagged = TRUE;
	else
		n_flagged = FALSE;
	free(unquoted);
	return (n_flagged);
}

void	ft_echo(char *usr_in, int write_fd)
{
	char	**words;
	char	*unquoted;
	t_bool	n_flagged;
	size_t	inx;

	set_exit_status(EXIT_SUCCESS);
	words = ft_word_split(usr_in, ft_isspace);
	if (!words)
		return (set_exit_status(EXIT_FAILURE));
	n_flagged = has_n_flag(words);
	inx = 1;
	if (n_flagged)
		inx = 2;
	while (words[inx])
	{
		unquoted = remove_quotes_from_word(words[inx], ft_strlen(words[inx]));
		ft_putstr_fd(unquoted, write_fd);
		if (words[inx + 1])
			ft_putchar_fd(' ', write_fd);
		free(unquoted);
		inx++;
	}
	if (!n_flagged)
		ft_putchar_fd('\n', write_fd);
	ft_free_char_matrix(&words);
}
