/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:05 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:10:19 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long double	ft_atold(const char *s)
{
	long double	num;
	long double	sign;

	num = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == 45)
		sign = -1;
	if (*s == 43 || *s == 45)
		s++;
	while (*s >= 48 && *s <= 57)
	{
		num = 10 * num + *s - 48;
		s++;
	}
	return (num * sign);
}

static void	exit_error(char *arg, char *err_msg)
{
	char	*unquoted;

	ft_putstr_fd("exit: ", 2);
	if (!arg)
	{
		ft_putendl_fd(err_msg, 2);
		return ;
	}
	unquoted = remove_quotes_from_word(arg, ft_strlen(arg));
	ft_putstr_fd(unquoted, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err_msg, 2);
	free(unquoted);
	return ;
}

static t_bool	is_considered_digit_str(const char *str)
{
	if (!str || !*str || ((*str != '-' && *str != '+') && !ft_isdigit(*str)))
		return (FALSE);
	if (ft_atold(str) != (long double)(ft_atoll(str)))
		return (FALSE);
	str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	exit_handler(char **params, t_pipe *pipe_lst, t_builtin *builds)
{
	int		exit_status;

	if (!params[1])
		exit_status = ft_atoi(var_lst_find_var("?", *g_env)->value);
	else if (!is_considered_digit_str(params[1]))
	{
		exit_error(params[1], "numeric argument required");
		exit_status = BUILTIN_MISUSE_CODE;
	}
	else if (params[2])
	{
		ft_free_char_matrix(&params);
		exit_error(NULL, "too many arguments");
		return (set_exit_status(EXIT_FAILURE));
	}
	else
		exit_status = ft_atoi(params[1]);
	ft_free_char_matrix(&params);
	rl_clear_history();
	pipe_lst_clear(&pipe_lst);
	free(builds);
	var_lst_clear(g_env);
	free(g_env);
	return (exit(exit_status));
}

void	ft_exit(char *usr_in, t_pipe *pipe_lst, t_builtin *builds,
	t_bool print)
{
	char	**params;
	char	*unquoted;

	params = ft_word_split(usr_in, ft_isspace);
	if (!params)
		return (exit(EXIT_FAILURE));
	if (print == TRUE)
		ft_putendl_fd("exit", 2);
	if (params[1])
	{
		unquoted = remove_quotes_from_word(params[1], ft_strlen(params[1]));
		free(params[1]);
		params[1] = unquoted;
	}
	exit_handler(params, pipe_lst, builds);
}
