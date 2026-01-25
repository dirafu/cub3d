/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:45:13 by vlchinen          #+#    #+#             */
/*   Updated: 2025/02/21 11:57:48 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*file;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
	{
		if (file)
		{
			free(file);
			file = 0;
		}
		return (NULL);
	}
	file = read_buff_and_join_file(fd, buff, file);
	if (!file)
		return (NULL);
	line = pick_a_line(file);
	if (!line)
		file = NULL;
	file = trim_fst_line(file);
	return (line);
}

char	*pick_a_line(char *file)
{
	char	*line;
	char	temp;
	int		nl;
	size_t	i;

	i = 0;
	nl = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (file[i] == '\n')
	{
		temp = file[i + 1];
		file[i + 1] = '\0';
		nl = 1;
	}
	line = ft_strdup_gnl(file);
	if (nl)
		file[i + 1] = temp;
	if (!line)
		free(file);
	return (line);
}

char	*trim_fst_line(char *file)
{
	char	*new_file;
	size_t	i;

	if (!file)
		return (NULL);
	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (file[i] == '\n')
		i++;
	if (!file[i])
	{
		free(file);
		return (NULL);
	}
	new_file = ft_strdup_gnl(&file[i]);
	free(file);
	return (new_file);
}

void	free_buff_and_file(char	*buff, char *file)
{
	free(buff);
	free(file);
}
