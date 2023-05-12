/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:13:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/21 17:25:20 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_pid = 0;

void	init_data(t_mini *mini)
{
	mini->envs = NULL;
	mini->cmd_exit_status = 0;
	mini->last_exit_status = 0;
	mini->tmpfile = "tmpfile";
	mini->exec_loop = (t_exec_loop *)malloc(sizeof(t_exec_loop));
	mini->exec_loop->redirect_file_path = NULL;
	mini->exec_loop->right_path = NULL;
}

char	*get_prompt(t_mini *mem)
{
	char	*prompt;
	char	*pwd;
	char	*temp;
	char	*start;

	pwd = get_env_val(mem, "PWD", mem->cmd_exit_status);
	if (ft_strcmp(pwd, ""))
	{
		temp = ft_strjoin(COLOR_CYAN, pwd);
		start = ft_strjoin(temp, COLOR_RESET);
		free(temp);
	}
	else
		start = ft_strdup(COLOR_CYAN "minishell" COLOR_RESET);
	free(pwd);
	if (mem->cmd_exit_status == 0)
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
		exit(free_t_mini(mem, 0));
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

	command_list = NULL;
	args = NULL;
	if (!check_quotes(command) || !split_args(&args, command)
		|| check_specials(args) || !fill_cmd_list(&command_list, args))
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
	char		*env;

	(void)argc, (void)argv;
	g_pid = 0;
	init_data(&mini);
	start_handles();
	load_env_vars(&mini, envs);
	env = get_env_val(&mini, "PATH", 0);
	mini.path_tab = ft_split(env, '\0');
	free(env);
	while (1)
	{
		input = take_input(&mini);
		if (!input)
			continue ;
		command_list = parsing_args(input);
		free(input);
		if (!command_list)
			continue ;
		execute(command_list, &mini);
		cmd_clear(&command_list);
	}
	return (free_t_mini(&mini, 0));
}
