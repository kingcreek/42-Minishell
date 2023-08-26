/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:29:13 by imurugar          #+#    #+#             */
/*   Updated: 2023/08/26 05:01:36 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_helper(t_var *temp, t_var *current)
{
	while (temp->next != NULL && \
		ft_strcmp(current->name, temp->next->name) >= 0)
		temp = temp->next;
	current->next = temp->next;
	temp->next = current;
}

t_var	*sort_variables(const t_var *head)
{
	t_var	*sorted;
	t_var	*current;
	t_var	*next;
	t_var	*temp;

	if (head == NULL || head->next == NULL)
		return ((t_var *)head);
	sorted = NULL;
	current = (t_var *)head;
	while (current != NULL)
	{
		next = current->next;
		if (sorted == NULL || ft_strcmp(current->name, sorted->name) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			temp = sorted;
			sort_helper(temp, current);
		}
		current = next;
	}
	return (sorted);
}

void	add_oldpwd(t_var **copy)
{
	t_var	*oldpwd_node;
	t_var	*prev_node;
	t_var	*new_node;

	oldpwd_node = *copy;
	prev_node = NULL;
	while (oldpwd_node != NULL && ft_strcmp(oldpwd_node->name, "OLDPWD") != 0)
	{
		prev_node = oldpwd_node;
		oldpwd_node = oldpwd_node->next;
	}
	if (oldpwd_node == NULL || ft_strcmp(oldpwd_node->name, "OLDPWD") != 0)
	{
		new_node = malloc(sizeof(t_var));
		if (!new_node)
			exit(0);
		new_node->name = ft_strdup("OLDPWD");
		new_node->value = NULL;
		new_node->next = oldpwd_node;
		if (prev_node == NULL)
			(*copy) = new_node;
		else
			prev_node->next = new_node;
	}
}

void	copy_env(t_var **copy)
{
	t_var	*iterator;
	t_var	*current;
	t_var	*new_node;

	iterator = *g_env;
	current = NULL;
	while (iterator)
	{
		new_node = malloc(sizeof(t_var));
		new_node->name = ft_strdup(iterator->name);
		if (iterator->value != NULL)
			new_node->value = ft_strdup(iterator->value);
		new_node->next = NULL;
		if (*copy == NULL)
		{
			(*copy) = new_node;
			current = *copy;
		}
		else
		{
			current->next = new_node;
			current = current->next;
		}
		iterator = iterator->next;
	}
}

void	print_helper(t_var *copy, int write_fd)
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
