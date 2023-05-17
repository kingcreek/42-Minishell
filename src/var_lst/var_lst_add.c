/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:52:04 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 03:48:51 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_lst_new(char *name, char *value)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	var_lst_add_back(t_var **lst, t_var *new)
{
	t_var	*head;

	if (!*lst)
		*lst = new;
	else
	{
		head = *lst;
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		*lst = head;
	}
}

void	var_lst_add_front(t_var **lst, t_var *new)
{
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}

void	var_lst_add_var(t_var **lst, t_var *new)
{
	t_var	*old;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	old = var_lst_find_var(new->name, *lst);
	if (old)
	{
		free(old->value);
		if (new->value)
			old->value = ft_strdup(new->value);
		else
			old->value = NULL;
		var_lst_delete_node(new);
		return ;
	}
	var_lst_add_front(lst, new);
}
