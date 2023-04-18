/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:00:25 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 14:32:13 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmdlist_len(t_cmdlst *lst)
{
	int	cur;

	cur = 0;
	while (lst)
	{
		cur++;
		lst = lst->next;
	}
	return (cur);
}

int	lst_append(t_list **lst, char *str)
{
	t_list	*new;

	new = ft_lstnew(str);
	if (!new)
		return (lst_clear(&new));
	ft_lstadd_back(lst, new);
	return (1);
}

/*
	Return the len of an str array (that is 0-terminated)
*/
int	strarr_len(char **array)
{
	int	cur;

	cur = 0;
	if (array)
		while (array[cur])
			cur++;
	return (cur);
}

/*
	Append the given str to the end of the given array
	It malloc an entire new array, duplicates the existing elements
	and duplicate the given string. Then it free the original
	array and replace it's pointer to the new array's one
	Return 0 on malloc error
*/
int	strarr_append(char ***array, char *str)
{
	char	**new;
	int		new_len;
	int		cur;

	new_len = strarr_len(*array) + 1;
	new = malloc(sizeof(char *) * (new_len + 1));
	if (!new)
		return (0);
	cur = 0;
	while ((*array) && (*array)[cur])
	{
		new[cur] = ft_strdup((*array)[cur]);
		if (!new[cur])
			return (free_array_n(new, cur));
		cur++;
	}
	new[cur] = ft_strdup(str);
	if (!new[cur])
		return (free_array_n(new, cur));
	cur++;
	new[cur] = 0;
	strarr_free(*array);
	*array = new;
	return (1);
}
