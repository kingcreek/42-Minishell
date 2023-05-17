/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:54:33 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/16 16:54:35 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	*init_builds(void)
{
	t_builtin	*builds;

	builds = malloc(sizeof(t_builtin) * 7);
	builds[0] = (t_builtin){"echo", (void *)ft_echo};
	builds[1] = (t_builtin){"env", (void *)ft_env};
	builds[2] = (t_builtin){"pwd", (void *)ft_pwd};
	builds[3] = (t_builtin){"cd", (void *)ft_cd};
	builds[4] = (t_builtin){"exit", (void *)ft_exit};
	builds[5] = (t_builtin){"export", (void *)ft_export};
	builds[6] = (t_builtin){"unset", (void *)ft_unset};
	return (builds);
}

int	hash_search(const char *key, t_builtin *builds)
{
	size_t		inx;

	inx = 0;
	while (inx < 7)
	{
		if (ft_strncmp(
				builds[inx].name, key, ft_strlen(builds[inx].name) + 1) == 0)
			return (inx);
		inx++;
	}
	return (7);
}
