/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:13:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/13 14:36:21 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_mini *mini)
{
	mini->envs = NULL;
	mini->cmds = NULL;
	mini->exit_status = 0;
}

char	*get_prompt(t_mini *mem)
{
	char	*prompt;
	char	*pwd;
	char	*temp;
	char	*start;

	pwd = get_env_val(mem, "PWD");
	if (pwd)
	{
		temp = ft_strjoin("\n\001\033[36m\002", pwd);
		free(pwd);
		start = ft_strjoin(temp, "\001\033[0m\002\n");
		free(temp);
	}
	else
		start = ft_strdup("\001\033[36m\002minishell\001\033[0m\002");
	if (mem->exit_status == 0)
		prompt = ft_strjoin(start, "\001\033[32m\002>\001\033[0m\002");
	else
		prompt = ft_strjoin(start, "\001\033[31m\002>\001\033[0m\002");
	free(start);
	return (prompt);
}

char	*take_input(t_mini *mem)
{
	char	*buf;
	char	*prompt;

	prompt = get_prompt(mem);
	buf = readline(prompt);
	free(prompt);
	if (!buf)
	{
		ft_putstr_fd("\n", 1);
		exit(free_t_mini(mem));
	}
	if (ft_strlen(buf) == 0)
	{
		free(buf);
		return (NULL);
	}
	add_history(buf);
	return (buf);
}

t_cmdlst	*parsing(char *command)
{
	t_cmdlst	*command_list;
	/*t_list		*args;

	args = NULL;
	*/
	if (check_quotes(command))
		return (NULL);
	printf("llega");
	/*
	if (!split_args(&args, command))
		return (NULL);
	*/
	if (check_specials(args))
	{
		lst_clear(&args);
		return (NULL);
	}
	/*
	if (!create_command_lst(&command_list, args))
	{
		lst_clear(&args);
		return (NULL);
	}
	lst_clear(&args);*/
	return (command_list);
}

int	main(int argc, char **argv, char **envs)
{
	t_mini		mini;
	t_cmdlst	*command_list;
	char		*input;

	(void)argc, (void)argv;
	init_data(&mini);
	start_handles();
	load_env_vars(&mini, envs);
	while (1)
	{
		input = take_input(&mini);
		
		if (!input)
			continue ;
		command_list = parsing(input);
		free(input);
		if (!command_list)
			continue ;
		//execute(command_list, &mini);
		//cmdlst_clear(&command_list);
	}
	return (free_t_mini(&mini));
}
