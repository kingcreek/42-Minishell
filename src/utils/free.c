/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:02:51 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 22:46:16 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The function frees a linked list of environment variables.
 * 
 * @param s The parameter `s` is a pointer to a pointer
 * to a struct of type `t_envs`. It is likely that
 * `t_envs` is a linked list node structure used to store environment variables.
 */
void	free_envs(t_envs **s)
{
	t_envs	*tmp;

	if (s)
	{
		while (*s)
		{
			tmp = (*s)->next;
			free((*s)->key);
			free(*s);
			(*s) = tmp;
		}
	}
}

/**
 * The function frees memory allocated for a
 * t_mini struct and returns its exit status.
 * 
 * @param mini `mini` is a pointer to a `t_mini` struct.
 * 
 * @return the exit status of the `t_mini` structure.
 */
int	free_t_mini(t_mini *mini, int exit)
{
	int	exit_status;

	exit_status = mini->last_exit_status;
	if (mini->envs)
		free_envs(&mini->envs);
	return (exit);
}

/**
 * The function frees the memory allocated for a string array.
 * 
 * @param arr a pointer to a char pointer (i.e. a pointer to a string array)
 * 
 * @return an integer value of 0.
 */
int	strarr_free(char **arr)
{
	int	cur;

	cur = -1;
	if (arr)
	{
		while (arr[++cur])
			free(arr[cur]);
		free(arr);
	}
	return (0);
}

/**
 * The function clears a linked list by freeing its content and nodes.
 * 
 * @param lst A pointer to a pointer to the first node of a linked list.
 * 
 * @return an integer value of 0.
 */
int	lst_clear(t_list **lst)
{
	t_list	*nxt;

	while (*lst)
	{
		nxt = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = nxt;
	}
	*lst = NULL;
	return (0);
}

int	outlst_clear(t_o_file **lst)
{
	t_o_file	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->filename);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
}

int	cmd_clear(t_cmdlst **lst)
{
	t_cmdlst	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->command);
		strarr_free((*lst)->args);
		strarr_free((*lst)->infiles);
		strarr_free((*lst)->heredocs);
		outlst_clear(&(*lst)->outfiles);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
	return (0);
}

int	free_array_n(char **array, int n)
{
	while (n--)
		free(array[n]);
	free(array);
	return (0);
}
