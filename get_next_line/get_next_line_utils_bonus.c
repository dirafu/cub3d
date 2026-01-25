/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:21:23 by vlchinen          #+#    #+#             */
/*   Updated: 2025/02/22 18:14:47 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_buff_and_join_file(int fd, char *buff, t_lst *lst, int fs)
{
	ssize_t	bytes_read;
	char	*line;

	while (fs || (bytes_read && !search_for_nl(lst->content)))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (fs && !bytes_read)
			break ;
		if (fs)
			fs = 0;
		if (bytes_read < 0)
		{
			lst->content = trim_fst_line(buff, lst->content, 1);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		if (!join_line(lst, buff, 0))
			break ;
	}
	free(buff);
	line = pick_a_line(lst->content);
	if (!line)
		lst->content = 0;
	lst->content = trim_fst_line(lst->content, 0, 0);
	return (line);
}

char	*join_line(t_lst *lst, char *buff, char *file)
{
	char	*new_file;
	size_t	i;
	size_t	j;

	if (lst)
		file = lst->content;
	if (!file)
		file = "";
	new_file = malloc(sizeof(char) * (ft_strlen(file) + ft_strlen(buff) + 1));
	if (!new_file && lst)
		lst->content = trim_fst_line(0, lst->content, 1);
	if (!new_file)
		return (NULL);
	i = 0;
	j = 0;
	while (file[i])
		new_file[i++] = file[j++];
	while (*buff)
		new_file[i++] = *buff++;
	new_file[i] = '\0';
	if (lst)
		free(lst->content);
	if (lst)
		lst->content = new_file;
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

t_lst	*search_lst(t_lst *lst, int fd)
{
	while (lst)
	{
		if (*(lst->fd) == fd)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
