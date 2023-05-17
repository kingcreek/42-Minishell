/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:53:13 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 03:47:47 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(int write_fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putendl_fd(path, write_fd);
	free(path);
	set_exit_status(EXIT_SUCCESS);
}
