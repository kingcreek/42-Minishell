/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   export_shorter.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: imurugar <imurugar@student.42madrid.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/07/05 20:43:18 by imurugar		  #+#	#+#			 */
/*   Updated: 2023/07/05 20:46:36 by imurugar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

t_var	*sort_variables(const t_var *head)
{
	t_var *sorted;
	t_var *current;
	t_var *next;
	t_var *temp;

	if (head == NULL || head->next == NULL)
		return ((t_var *)head);

	sorted = NULL;
	current = (t_var *)head;

	while (current != NULL)
	{
		next = current->next;
		if (sorted == NULL || strcmp(current->name, sorted->name) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			temp = sorted;
			while (temp->next != NULL && strcmp(current->name, temp->next->name) >= 0)
				temp = temp->next;
			current->next = temp->next;
			temp->next = current;
		}

		current = next;
	}

	return (sorted);
}
