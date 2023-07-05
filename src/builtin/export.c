/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   export.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: imurugar <imurugar@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/05/16 16:53:08 by imurugar		  #+#	#+#			 */
/*   Updated: 2023/07/05 20:59:50 by imurugar		 ###   ########.fr	   */
/*																			*/
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

void print_declarations(int write_fd)
{
	t_var *iterator = *g_env;

	// Crear una copia de la lista g_env
	t_var *copy = NULL;
	t_var *current = NULL;

	while (iterator)
	{
		t_var *new_node = malloc(sizeof(t_var));
		new_node->name = strdup(iterator->name);
		new_node->value = (iterator->value != NULL) ? strdup(iterator->value) : NULL;
		new_node->next = NULL;

		if (copy == NULL)
		{
			copy = new_node;
			current = copy;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}

		iterator = iterator->next;
	}

	// Agregar "OLDPWD" si no existe
	t_var *oldpwd_node = copy;
	t_var *prev_node = NULL;
	while (oldpwd_node != NULL && strcmp(oldpwd_node->name, "OLDPWD") < 0)
	{
		prev_node = oldpwd_node;
		oldpwd_node = oldpwd_node->next;
	}

	if (oldpwd_node == NULL || strcmp(oldpwd_node->name, "OLDPWD") != 0)
	{
		t_var *new_node = malloc(sizeof(t_var));
		new_node->name = strdup("OLDPWD");
		new_node->value = NULL;
		new_node->next = oldpwd_node;

		if (prev_node == NULL)
			copy = new_node;
		else
			prev_node->next = new_node;
	}

	// Ordenar la lista copiada
	sort_variables(copy);

	// Imprimir las declaraciones en orden alfabético
	while (copy)
	{
		if (strncmp(copy->name, "?", 2) != 0)
		{
			ft_putstr_fd("declare -x ", write_fd);
			ft_putstr_fd(copy->name, write_fd);
			if (copy->value != NULL)
			{
				ft_putstr_fd("=\"", write_fd);
				ft_putstr_fd(copy->value, write_fd);
				ft_putstr_fd("\"", write_fd);
			}
			ft_putchar_fd('\n', write_fd);
		}

		t_var *next = copy->next;
		free(copy->name);
		free(copy->value);
		free(copy);
		copy = next;
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
