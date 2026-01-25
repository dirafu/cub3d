/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:49:40 by vlchinen          #+#    #+#             */
/*   Updated: 2025/02/21 13:25:15 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buff_and_join_file(int fd, char *buff, char *file)
{
	ssize_t	bytes_read;
	int		fs;

	fs = 1;
	while (fs || (bytes_read && !search_for_nl(file)))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (fs)
		{
			if (!bytes_read)
				break ;
			fs = 0;
		}
		if (bytes_read < 0)
		{
			free_buff_and_file(buff, file);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		file = join_line(file, buff);
		if (!file)
			break ;
	}
	free(buff);
	return (file);
}

char	*join_line(char *file, char *buff)
{
	char	*new_file;
	size_t	i;

	if (!file)
		return (ft_strdup_gnl(buff));
	new_file = malloc(sizeof(char) * (ft_strlen_gnl(file)
				+ ft_strlen_gnl(buff) + 1));
	if (!new_file)
	{
		free(file);
		return (NULL);
	}
	i = 0;
	while (file[i])
	{
		new_file[i] = file[i];
		i++;
	}
	while (*buff)
		new_file[i++] = *buff++;
	new_file[i] = '\0';
	free(file);
	return (new_file);
}

int	search_for_nl(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *str)
{
	char	*new_str;
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	new_str = malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
