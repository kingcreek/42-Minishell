/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:13:47 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/10 13:08:44 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	set_envs(t_mini *mini, char **env)
{
	t_envs	*tmp;
	t_envs	*ret;

	(void)mini;
	while (*env)
	{
		tmp = stack_new(*env);
		add_back(&ret, tmp);
		env++;
	}
}
*/

char	*ft_strtok(char *str, const char *delim)
{
	char	*p;
	char	*start;

	p = NULL;
	if (str != NULL)
	{
		p = str;
	}
	else if (p == NULL || *p == '\0')
	{
		return (NULL);
	}
	start = p;
	while (*p && ft_strchr(delim, *p) == NULL)
	{
		p++;
	}
	if (*p)
	{
		*p++ = '\0';
	}
	return (start);
}

int	tokenize_input(char *input, char *tokens[])
{
	int		n_tokens;
	char	*token;

	n_tokens = 0;
	token = ft_strtok(input, " \n");
	while (token != NULL)
	{
		tokens[n_tokens++] = token;
		token = ft_strtok(NULL, " \n");
	}
	tokens[n_tokens] = NULL;
	return (n_tokens);
}

void	execute_command(char **tokens)
{
	if (execvp(tokens[0], tokens) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envs)
{
	//t_mini	mini;
	char	*input;
	int		status;

	if (argc > 1)
	{
		printf("No se necesitan parametros?");
		exit(EXIT_FAILURE);
	}
	(void)argv;
	(void)envs;
	start_handles();
	//set_envs(&mini, envs);

	while (1)
	{
		input = readline("ArIm$ ");
		if (!input)
		{
			printf("exit 1\n");
			exit (EXIT_SUCCESS);
		}
		else if (ft_strcmp(input, "exit") == 0)
		{
			printf("exit 2\n");
			free(input);
			exit (EXIT_SUCCESS);
		}
		else
		{
			add_history(input); // add to history ?
			pid_t pid = fork(); //create a child process
			if (pid < 0)
			{
				// Error when create a child process
				printf("Error: no se pudo crear el proceso hijo, pid: %d\n", pid);
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				char* args[] = { "ls", "-la", NULL };
				// Child process execute the command
				if (execve(args[0], args, NULL) < 0)
				{
					// Error executing the command
					printf("Error: no se pudo ejecutar el comando %s\n", input);
					exit(EXIT_FAILURE);
				}
				printf("3\n");
			}
			else
			{
				// The parent process waits for the child to finish
				printf("4\n");
				waitpid(pid, &status, 0);
			}
			
			free(input);
		}
	}
	return (EXIT_SUCCESS);
}
