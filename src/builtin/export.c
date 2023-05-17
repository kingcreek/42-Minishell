/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:08 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:11:52 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	invalid_name_error(char *var_name)
{
	char	*unquoted;

	unquoted = remove_quotes_from_word(var_name, ft_strlen(var_name));
	set_exit_status(EXIT_FAILURE);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(unquoted, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(unquoted);
}

static t_var	*get_export_var(char **export_words)
{
	size_t	inx;
	t_var	*export_vars_lst;
	t_var	*new_var;

	export_vars_lst = NULL;
	inx = 1;
	while (export_words[inx])
	{
		new_var = get_var_from_assignment(export_words[inx]);
		if (!is_valid_varname(new_var->name))
		{
			invalid_name_error(export_words[inx]);
			var_lst_delete_node(new_var);
		}
		else
			var_lst_add_front(&export_vars_lst, new_var);
		inx++;
	}
	return (export_vars_lst);
}

static void	update_environment(t_var *export)
{
	t_var	*var;

	while (export)
	{
		var = var_lst_find_var(export->name, *g_env);
		if (ft_strncmp(export->name, "?", ft_strlen("?")) == 0)
			;
		else if (export->value != NULL)
			var_lst_add_var(g_env, var_lst_new(ft_strdup(export->name),
					ft_strdup(export->value)));
		else if (var != NULL && var->value != NULL)
			var_lst_add_var(g_env,
				var_lst_new(ft_strdup(var->name), ft_strdup(var->value)));
		else if (var != NULL)
			var_lst_add_var(g_env, var_lst_new(ft_strdup(var->name), NULL));
		else
			var_lst_add_var(g_env, var_lst_new(ft_strdup(export->name), NULL));
		export = export->next;
	}
}

static void	print_declarations(int write_fd)
{
	t_var	*iterator;

	iterator = *g_env;
	while (iterator)
	{
		if (ft_strncmp(iterator->name, "?", 2) != 0)
		{
			ft_putstr_fd("declare -x ", write_fd);
			ft_putstr_fd(iterator->name, write_fd);
			if (iterator->value != NULL)
			{
				ft_putstr_fd("=\"", write_fd);
				ft_putstr_fd(iterator->value, write_fd);
				ft_putstr_fd("\"", write_fd);
			}
			ft_putchar_fd('\n', write_fd);
		}
		iterator = iterator->next;
	}
	set_exit_status(EXIT_SUCCESS);
}

void	ft_export(char *usr_in, int write_fd)
{
	char	**words;
	t_var	*vars;

	set_exit_status(EXIT_SUCCESS);
	words = ft_word_split(usr_in, ft_isspace);
	if (!words)
		return (set_exit_status(EXIT_FAILURE));
	vars = NULL;
	if (words[0] && words[1] == NULL)
		print_declarations(write_fd);
	else
		vars = get_export_var(words);
	ft_free_char_matrix(&words);
	if (!vars)
		return ;
	update_environment(vars);
	var_lst_clear(&vars);
}
