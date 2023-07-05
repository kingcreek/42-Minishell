/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:53 by imurugar          #+#    #+#             */
/*   Updated: 2023/07/04 14:08:26 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_input(char *input, char *old_input, char *delimiter)
{
	if (!input && get_exit_status() == 130)
	{
		free(old_input);
		return (-1);
	}
	else if (!input && old_input && *old_input
		&& old_input[ft_strlen(old_input) - 1] == '\n')
	{
		ft_putstr_fd(MINISHELL_ERROR, STDERR_FILENO);
		ft_putstr_fd(EOF_ERROR, STDERR_FILENO);
		ft_putstr_fd(delimiter, STDERR_FILENO);
		ft_putstr_fd("')", STDERR_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	write_to_file(int w_fd, char **input, char **old)
{
	find_var_and_expand(input, FALSE);
	ft_putstr_fd(*input, w_fd);
	free(*old);
	*old = ft_strdup(*input);
	ft_null_free((void *)(input));
}

static t_bool	here_doc_loop(int w_fd, char *input, char *delimiter)
{
	char	*old;
	int		status;

	old = ft_strdup("\n");
	while (!input || ft_strlen(input) != ft_strlen(delimiter) + 1
		|| ft_strncmp(input, delimiter, ft_strlen(input) - 1) != 0
		|| input[ft_strlen(input) - 1] != '\n')
	{
		if (input)
			write_to_file(w_fd, &input, &old);
		if (old && *old && old[ft_strlen(old) - 1] == '\n')
			ft_putstr_fd("> ", STDOUT_FILENO);
		input = get_next_line(STDIN_FILENO);
		status = is_valid_input(input, old, delimiter);
		if (status == EXIT_FAILURE)
			break ;
		else if (status == -1)
			return (FALSE);
	}
	free(old);
	free(input);
	return (TRUE);
}

t_bool	here_doc(char *delimiter, t_shell *shell)
{
	char	*input;
	int		rw_pipe[2];

	pipe(rw_pipe);
	input = NULL;
	if (get_exit_status() == 130)
		set_exit_status(EXIT_SUCCESS);
	if (here_doc_loop(rw_pipe[1], input, delimiter) == FALSE)
	{
		close(rw_pipe[0]);
		close(rw_pipe[1]);
		return (FALSE);
	}
	close(rw_pipe[1]);
	shell->infile = rw_pipe[0];
	return (TRUE);
}
