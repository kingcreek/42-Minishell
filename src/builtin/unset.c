/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:17 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:12:07 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	invalid_name_error(char *var_name)
{
	set_exit_status(EXIT_FAILURE);
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

void	ft_unset(char *usr_in)
{
	char	**words;
	char	*var_name;
	size_t	inx;

	set_exit_status(EXIT_SUCCESS);
	words = ft_word_split(usr_in, ft_isspace);
	if (!words)
		return (set_exit_status(EXIT_FAILURE));
	if (words[0] && words[1] == NULL)
		return (ft_free_char_matrix(&words));
	inx = 1;
	while (words[inx])
	{
		var_name = remove_quotes_from_word(words[inx], ft_strlen(words[inx]));
		if (!is_valid_varname(var_name))
			invalid_name_error(var_name);
		else
			var_lst_delete_var(g_env, var_name);
		free(var_name);
		inx++;
	}
	ft_free_char_matrix(&words);
}
