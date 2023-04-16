/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:13:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/16 16:30:04 by imurugar         ###   ########.fr       */
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
		temp = ft_strjoin(COLOR_CYAN, pwd);
		free(pwd);
		start = ft_strjoin(temp, COLOR_RESET "\n");
		free(temp);
	}
	else
		start = ft_strdup(COLOR_CYAN "minishell" COLOR_RESET);
	if (mem->exit_status == 0)
		prompt = ft_strjoin(start, COLOR_GREEN ">" COLOR_RESET);
	else
		prompt = ft_strjoin(start, COLOR_RED ">" COLOR_RESET);
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

t_cmdlst	*parsing_args(char *command)
{
	t_cmdlst	*command_list;
	t_list		*args;

	args = NULL;
	if (check_quotes(command))
		return (NULL);
	if (!split_args(&args, command))
		return (NULL);
	if (check_specials(args))
	{
		lst_clear(&args);
		return (NULL);
	}
	if (!fill_cmd_list(&command_list, args))
	{
		lst_clear(&args);
		return (NULL);
	}
	lst_clear(&args);
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
		command_list = parsing_args(input);
		free(input);
		if (!command_list)
			continue ;
		//execute(command_list, &mini);
		//cmdlst_clear(&command_list);
	}
	return (free_t_mini(&mini));
}
