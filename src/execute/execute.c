/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:34:41 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/12 16:40:47 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_mini *mini, t_cmdlst *lst)
{
	
	if (ft_strcmp(lst->command, "cd") == 0
		|| ft_strcmp(lst->command, "exit") == 0
		|| ft_strcmp(lst->command, "export") == 0
		|| ft_strcmp(lst->command, "unset") == 0)
		return (0);
	if (ft_strcmp(lst->command, "pwd") == 0)
		ft_pwd(mini);
	if (ft_strcmp(lst->command, "env") == 0)
		ft_env(mini);
	if (ft_strcmp(lst->command, "echo") == 0)
		ft_echo(lst->args, mini);
	
	return (1);
}


int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (2);
	if (ft_strcmp(cmd, "exit") == 0)
		return (2);
	if (ft_strcmp(cmd, "export") == 0)
		return (2);
	if (ft_strcmp(cmd, "unset") == 0)
		return (2);
	return (0);
}

char	*try_path(char **path_tab, char *cmd, char *right_path, int i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	right_path = malloc(sizeof(char) * 150);
	while (path_tab[i][j])
		right_path[x++] = path_tab[i][j++];
	right_path[x] = '/';
	x++;
	j = 0;
	while (cmd[j])
		right_path[x++] = cmd[j++];
	right_path[x] = '\0';
	if (access(right_path, F_OK) == 0)
		return (right_path);
	free(right_path);
	return (NULL);
}

char	*find_exec_path(char **path_tab, char *cmd, char *right_path)
{
	int	i;

	if (cmd[0] == '.' || cmd[0] == '/')
		return (ft_strdup(cmd));
	if (!path_tab)
		return (NULL);
	i = 0;
	while (path_tab[i])
	{
		right_path = try_path(path_tab, cmd, right_path, i);
		if (right_path)
			return (right_path);
		i++;
	}
	return (NULL);
}

void	init_exec_cmd(t_mini *mini, t_cmdlst *lst)
{
	mini->exec_path = NULL;
	mini->path_env = get_env_val(mini, "PATH", 0);
	if (mini->path_tab)
		strarr_free(mini->path_tab);
	mini->path_tab = ft_split(mini->path_env, ':');
	mini->exec_path = find_exec_path(mini->path_tab, lst->command,
			mini->exec_path);
}

void	exec_verif(t_cmdlst *lst)
{
	if (ft_strcmp(lst->command, "<<") == 0)
	{
		if (lst->command == NULL)
			return ;
		lst->command = lst->args[0];
	}
	return ;
}

void	exec_cmd(t_mini *mini, t_cmdlst *lst)
{
	char	**envs;

	envs = get_all_env(mini);
	exec_verif(lst);
	init_exec_cmd(mini, lst);
	if (is_builtin(lst->command))
	{
		//printf("is_builtin!");
		if (!exec_builtin(mini, lst))
			exit(0);
	}
	else
	{
		if (execve(mini->exec_path, lst->args, envs) == -1)
		{
			if (errno == 14 || errno == 13)
				print_error(errno, lst->command);
			else
				printf("%d %s\n", errno, strerror(errno));
			if (errno == 14)
				exit(127);
			free_paths(mini);
			exit(1);
		}
	}
	strarr_free(envs);
	free_paths(mini);
	exit(0);
}

char	*find_path_redirect_file(char *pwd, char *actuel, char *redirect_path)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	redirect_path = malloc(sizeof(char) * (ft_strlen(pwd)
				+ ft_strlen(actuel) + 3));
	if (!redirect_path)
		return (NULL);
	while (pwd[i])
		redirect_path[j++] = pwd[i++];
	redirect_path[j] = '/';
	j++;
	i = 0;
	while (actuel[i])
		redirect_path[j++] = actuel[i++];
	redirect_path[j] = '\0';
	return (redirect_path);
}

void	set_up_outfiles(t_mini *mini, t_cmdlst *lst)
{
	if (lst->outfiles->action == 0)
	{
		mini->exec_loop->redirect_file_path
			= find_path_redirect_file(getenv("PWD"),
				lst->outfiles->filename, mini->exec_loop->redirect_file_path);
			mini->exec_loop->fdout = open(mini->exec_loop->redirect_file_path,
				O_CREAT | O_WRONLY | O_TRUNC, S_IRWXO | S_IRWXU | S_IRWXG);
	}
	else if (lst->outfiles->action == 1)
	{
		mini->exec_loop->redirect_file_path
			= find_path_redirect_file(getenv("PWD"),
				lst->outfiles->filename, mini->exec_loop->redirect_file_path);
			mini->exec_loop->fdout = open(mini->exec_loop->redirect_file_path,
				O_APPEND | O_CREAT | O_WRONLY, S_IRWXO | S_IRWXU | S_IRWXG);
	}
}

void	set_up_output(t_mini *mini, t_cmdlst *lst, int i)
{
	if (i > 0)
		lst->outfiles = lst->outfiles->next;
	if (lst->todo_next != 1)
	{
		if (lst->outfiles)
			set_up_outfiles(mini, lst);
		else
			mini->exec_loop->fdout = dup(mini->exec_loop->tmpout);
	}
	else
	{
		pipe(mini->exec_loop->fdpipe);
		mini->exec_loop->fdout = mini->exec_loop->fdpipe[1];
		mini->exec_loop->fdin = mini->exec_loop->fdpipe[0];
	}
}

void	init_outlst_loop(t_mini *mini, t_cmdlst *lst, int i)
{
	dup2(mini->exec_loop->fdin, 0);
	close(mini->exec_loop->fdin);
	set_up_output(mini, lst, i);
	dup2(mini->exec_loop->fdout, 1);
	close(mini->exec_loop->fdout);
}

int	do_builtin(t_cmdlst *lst, t_mini *mini)
{
	if (ft_strcmp(lst->command, "cd") == 0 && lst->todo_next != 1)
		ft_cd(lst->args, mini);
	if (ft_strcmp(lst->command, "export") == 0 && lst->todo_next != 1)
		if (!ft_export(mini, lst->args))
			return (0);
	if (ft_strcmp(lst->command, "unset") == 0 && lst->todo_next != 1)
		if (!ft_unset(mini, lst->args))
			return (0);
	return (1);
}

void	ex(t_cmdlst *lst, t_mini *mini, int i)
{
	init_outlst_loop(mini, lst, i);
	g_pid = fork();
	//printf("pid: %d\n", g_pid);
	//printf("cmd: %s\n", lst->command);
	if (g_pid == 0)
		exec_cmd(mini, lst);
	waitpid(g_pid, &(mini->cmd_exit_status), 0);
	g_pid = 0;
	mini->cmd_exit_status = WEXITSTATUS(mini->cmd_exit_status);
	
	if ((ft_strcmp(lst->command, "cd") == 0 && lst->todo_next != 1)
		|| (ft_strcmp(lst->command, "export") == 0 && lst->todo_next != 1)
		|| (ft_strcmp(lst->command, "unset") == 0 && lst->todo_next != 1))
		do_builtin(lst, mini);
	/*if (lst->heredocs)
		delete_tpmfile(mini);*/
}

void	init_exec(t_mini *mini, t_cmdlst *lst)
{
	mini->exec_loop->tmpin = dup(0);
	mini->exec_loop->tmpout = dup(1);
	if (lst->infiles)
		mini->exec_loop->fdin = open(lst->infiles[0], O_RDONLY);
	else
		mini->exec_loop->fdin = dup(mini->exec_loop->tmpin);
	mini->cmd_exit_status = 0;
}

void	reset_exec(t_mini *mini)
{
	dup2(mini->exec_loop->tmpin, 0);
	dup2(mini->exec_loop->tmpout, 1);
	close(mini->exec_loop->tmpin);
	close(mini->exec_loop->tmpout);
	if (mini->exec_loop->redirect_file_path)
		free(mini->exec_loop->redirect_file_path);
	mini->exec_loop->redirect_file_path = NULL;
	mini->exec_loop->right_path = NULL;
	mini->cmd_exit_status = 0;
}

int	save_last_exit_status(t_mini *mini, t_cmdlst *lst)
{
	mini->last_exit_status = mini->cmd_exit_status;
	if (mini->cmd_exit_status == 0 && lst->todo_next == 3)
		return (1);
	if (mini->cmd_exit_status != 0 && lst->todo_next == 2)
		return (1);
	if (lst->todo_next == 2 || lst->todo_next == 3)
	{
		reset_exec(mini);
		init_exec(mini, lst);
	}
	return (0);
}

void	handle_heredocs(t_mini *mini, t_cmdlst *lst)
{
	int		fd;
	char	*buf;

	fd = open(mini->tmpfile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		return ;
	buf = readline(" >> ");
	while (1)
	{
		if (!buf)
			break ;
		if (ft_strcmp(buf, lst->heredocs[0]) == 0)
			break ;
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		buf = readline(" >> ");
	}
	if (buf)
		free(buf);
	close(fd);
	mini->exec_loop->fdin = open(mini->tmpfile, O_RDONLY, 0777);
	dup2(mini->exec_loop->fdin, STDIN_FILENO);
	close(mini->exec_loop->fdin);
}

void	setup_infiles(t_cmdlst *lst, t_mini *mini)
{
	if (lst->infiles)
		mini->exec_loop->fdin = open(lst->infiles[0], O_RDONLY);
	if (lst->heredocs)
	{
		reset_exec(mini);
		init_exec(mini, lst);
		handle_heredocs(mini, lst);
	}
}

void	execute(t_cmdlst *lst, t_mini *mini)
{
	int	i;

	mini->exec_loop->redirect_file_path = NULL;
	init_exec(mini, lst);
	while (lst)
	{
		setup_infiles(lst, mini);
		if (is_exit(lst))
			ft_exit(mini, lst);
		if (lst->args)
			expand_env(lst->args, mini);
		if (outlst_len(lst->outfiles) > 0)
			i = 0;
		else
			i = -1;
		while (i < outlst_len(lst->outfiles))
		{
			//printf("%s \n", lst->command);
			ex(lst, mini, i);
			i++;
		}
		if (save_last_exit_status(mini, lst))
			lst = lst->next;
		lst = lst->next;
	}
	reset_exec(mini);
}
