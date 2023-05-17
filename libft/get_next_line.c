/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 04:02:32 by imurugar          #+#    #+#             */
/*   Updated: 2023/05/17 04:02:33 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*build_line(int fd, char **acc, char **buffer);
static char		*nl_in_backup(char **acc);
static char		*nl_in_buffer(char **acc, char **buffer);
static ssize_t	validated_read(int fd, char **acc, char **buffer);

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buffer;
	ssize_t		read_val;
	char		*aux;

	aux = nl_in_backup(&backup);
	if (aux)
		return (aux);
	read_val = validated_read(fd, &backup, &buffer);
	if (read_val < 0)
		return (NULL);
	if (read_val == 0)
	{
		aux = NULL;
		if (backup && ft_strlen(backup))
			aux = ft_strdup(backup);
		if (backup)
			ft_null_free((void *)(&backup));
		free(buffer);
		return (aux);
	}
	return (build_line(fd, &backup, &buffer));
}

static char	*build_line(int fd, char **acc, char **buffer)
{
	char		*aux;

	aux = nl_in_buffer(acc, buffer);
	if (aux)
		return (aux);
	aux = ft_strjoin(*acc, *buffer);
	ft_null_free((void *)(acc));
	free(*buffer);
	*acc = ft_strdup(aux);
	free(aux);
	return (get_next_line(fd));
}

static char	*nl_in_backup(char **acc)
{
	char	*acc_nl;
	char	*result;
	char	*aux;

	if (!*acc || !**acc)
		return (NULL);
	acc_nl = ft_strchr(*acc, '\n');
	if (acc_nl)
	{
		aux = ft_strdup(acc_nl + 1);
		result = ft_substr(*acc, 0, acc_nl - *acc + 1);
		free(*acc);
		*acc = ft_strdup(aux);
		free(aux);
		return (result);
	}
	return (NULL);
}

static char	*nl_in_buffer(char **acc, char **buffer)
{
	char		*temp;
	char		*aux;
	char		*nl;

	if (!*acc)
		*acc = ft_strdup("");
	nl = ft_strchr(*buffer, '\n');
	if (!nl)
		return (NULL);
	temp = ft_substr(*buffer, 0, nl - *buffer + 1);
	aux = ft_strjoin(*acc, temp);
	ft_null_free((void *)(&temp));
	if (nl == *buffer || *(nl + 1) != '\0')
	{
		free(*acc);
		*acc = ft_strdup(nl + 1);
	}
	else
		ft_null_free((void *)(acc));
	free(*buffer);
	return (aux);
}

static ssize_t	validated_read(int fd, char **acc, char **buffer)
{
	ssize_t		read_val;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (-1);
	read_val = read(fd, *buffer, BUFFER_SIZE);
	if (read_val < 0)
	{
		free(*buffer);
		if (*acc)
			ft_null_free((void *)(acc));
		return (-1);
	}
	*(*buffer + read_val) = '\0';
	return (read_val);
}
