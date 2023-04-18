/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:34:41 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/18 22:48:13 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_last_exit_status(t_mini *mem, t_cmdlst *lst)
{
	mem->last_exit_status = mem->cmd_exit_status;
	if (mem->cmd_exit_status == 0 && lst->todo_next == 3)
		return (1);
	if (mem->cmd_exit_status != 0 && lst->todo_next == 2)
		return (1);
	if (lst->todo_next == 2 || lst->todo_next == 3)
	{
		
	}
	return (0);
}

void	delete_tpmfile(t_mini *mem)
{
	char	**argv;
	pid_t	pid;

	argv = malloc(sizeof(char *) * 3);
	argv[0] = "/bin/rm";
	argv[1] = mem->tmpfile;
	argv[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/rm", argv, NULL);
}

void	execute(t_cmdlst *lst, t_mini *mini)
{
	int	i;

	while (lst)
	{
		if (is_exit(lst))
			ft_exit(mini, lst);
		expand_env(lst->args, mini);
		lst = lst->next;
	}
}
