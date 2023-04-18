/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 16:20:18 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 14:10:06 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdlst	*new_cmd(void)
{
	t_cmdlst	*new;

	new = malloc(sizeof(t_cmdlst));
	if (!new)
		return (0);
	new->command = NULL;
	new->next = NULL;
	new->todo_next = END;
	new->args = NULL;
	new->infiles = NULL;
	new->outfiles = NULL;
	new->heredocs = NULL;
	return (new);
}

t_cmdlst	*cmdlst_last(t_cmdlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

int	append_in_args(t_list **args, char *op, char ***array)
{
	if (!(*args))
		return (1);
	if (ft_strlen(op) == ft_strlen((*args)->content)
		&& !ft_strcmp((*args)->content, op))
	{
		*args = (*args)->next;
		if (*args && !strarr_append(array, (*args)->content))
			return (0);
		*args = (*args)->next;
	}
	return (1);
}

int	cmdlist_append_args(t_list **args, t_cmdlst *new)
{
	while (*args && !get_arg_type((*args)->content))
	{
		if (!append_out_args(args, ">", &(new->outfiles)))
			return (0);
		else if (!append_in_args(args, "<", &(new->infiles)))
			return (0);
		else if (!append_out_args(args, ">>", &(new->outfiles)))
			return (0);
		else if (!append_in_args(args, "<<", &(new->heredocs)))
			return (0);
		if ((*args) && !is_sep((*args)->content))
		{
			if (!strarr_append(&(new->args), (*args)->content))
				return (0);
			*args = (*args)->next;
		}
	}
	return (1);
}

int	fill_cmd_list(t_cmdlst **command_list, t_list *args)
{
	t_cmdlst	*new;

	*command_list = NULL;
	while (args && !get_arg_type(args->content))
	{
		new = new_cmd();
		if (!new)
			return (cmd_clear(command_list));
		if (*command_list)
			cmdlst_last(*command_list)->next = new;
		else
			*command_list = new;
		new->command = ft_strdup(args->content);
		if (!new->command)
			return (cmd_clear(command_list));
		if (!cmdlist_append_args(&args, new))
			return (cmd_clear(command_list));
		if (args)
			new->todo_next = get_arg_type(args->content);
		if (args)
			args = args->next;
	}
	return (1);
}
