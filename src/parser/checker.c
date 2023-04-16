/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:14:25 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/16 16:28:51 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function checks if the number of single
 * and double quotes in a string is even and returns an
 * error if it is not.
 * 
 * @param cmd The parameter `cmd` is a pointer to a
 * character array representing a command string.
 * 
 * @return a boolean value (0 or 1) indicating whether there
 * is an error in the quotes of the command
 * string. If there is an error, the function calls the
 * `print_error` function with an error code of 1
 * and a NULL argument.
 */
int	check_quotes(char *cmd)
{
	int	len;
	int	single_quotes;
	int	double_quotes;
	int	i;

	len = strlen(cmd);
	single_quotes = 0;
	double_quotes = 0;
	i = 0;
	while (i < len)
	{
		if (cmd[i] == '\'')
		{
			single_quotes++;
		}
		else if (cmd[i] == '\"')
		{
			double_quotes++;
		}
		i++;
	}
	i = ((single_quotes % 2 == 0) && (double_quotes % 2 == 0)) == 0;
	if (i != 0)
		print_error(1, NULL);
	return (i);
}
/*
int	strcmp_len(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)));
}
*/

/**
 * The function returns an integer value based on
 * the type of argument passed as a string.
 * 
 * @param str A pointer to a string that represents
 * a command or operator in a shell script.
 * 
 * @return The function `get_arg_type` takes a string as
 * input and returns an integer value based on
 * the type of argument. If the string is equal to `"|"`,
 * it returns the value `PIPE`. If the string is
 * equal to `"&&"`, it returns the value `AND`.
 * If the string is equal to `"||"`, it returns the value `OR`.
 * If the string is equal to
 */
int	get_arg_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, "&&"))
		return (AND);
	if (!ft_strcmp(str, "||"))
		return (OR);
	if (!ft_strcmp(str, ";"))
		return (CONTINUE);
	return (END);
}

/**
 * The function checks if a given string is a separator
 * in a shell command.
 * 
 * @param str The parameter `str` is a pointer to a character
 * string that is being checked for being a
 * separator.
 * 
 * @return The function `is_sep` returns an integer value of 1
 * if the input string `str` is a separator
 * (">", "<", "<<", ">>", "&", or ";"), and 0 otherwise.
 */
int	is_sep(char *str)
{
	if (get_arg_type(str) != 0)
		return (1);
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, "<"))
		return (1);
	if (!ft_strcmp(str, "<<"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "&"))
		return (1);
	if (!ft_strcmp(str, ";"))
		return (1);
	return (0);
}

/**
 * The function checks if there are any special characters
 * in the given list of arguments and returns
 * an error if there are any invalid combinations.
 * 
 * @param args The parameter `args` is a pointer to a
 * linked list of strings, where each string
 * represents an argument passed to a command.
 * 
 * @return an integer value, which is either 0 if there are no errors,
 * or a non-zero value if there is
 * an error. The specific error codes and messages are defined in
 * the `print_error` function.
 */
int	check_specials(t_list *args)
{
	t_list	*it_args;
	int		is_special;

	it_args = args;
	is_special = 0;
	while (it_args)
	{
		if (is_sep(it_args->content))
		{
			if (is_special)
				return (print_error(2, it_args->content));
			is_special = 1;
		}
		else
			is_special = 0;
		if (!it_args->next)
		{
			if (is_sep(it_args->content) && ft_strcmp(it_args->content, ";"))
				return (print_error(3, it_args->content));
		}
		it_args = it_args->next;
	}
	return (0);
}
