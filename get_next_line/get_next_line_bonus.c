/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:12:47 by vlchinen          #+#    #+#             */
/*   Updated: 2025/02/22 18:16:31 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*del_or_append_node(t_lst **lst, t_lst *node, int mode)
{
	t_lst	*lst1;

	if (mode == 1 && lst && node)
	{
		if (node->prev)
			(node->prev)->next = node->next;
		else if (node->next)
			*lst = node->next;
		else
			*lst = NULL;
		if (node->next)
			(node->next)->prev = node->prev;
		free(node->fd);
		free(node->content);
		free(node);
	}
	else if (mode == 2)
	{
		lst1 = *lst;
		while (lst1->next)
			lst1 = lst1->next;
		lst1->next = node;
		node->prev = lst1;
	}
	return (NULL);
}

t_lst	*new_node(char *content, int fd)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	node->fd = malloc(sizeof(int));
	if (!node->fd)
	{
		free(node);
		return (NULL);
	}
	*(node->fd) = fd;
	node->prev = NULL;
	node->next = NULL;
	if (content)
		node->content = content;
	else
		node->content = NULL;
	return (node);
}

char	*get_next_line(int fd)
{
	char			*buff;
	char			*line;
	static t_lst	*files;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (del_or_append_node(&files, search_lst(files, fd), 1));
	if (!search_lst(files, fd))
	{
		if (!files)
		{
			files = new_node(0, fd);
			if (!files)
				return (trim_fst_line(0, buff, 1));
		}
		else
			del_or_append_node(&files, new_node(0, fd), 2);
	}
	line = read_buff_and_join_file(fd, buff, search_lst(files, fd), 1);
	if (!(search_lst(files, fd)->content))
		del_or_append_node(&files, search_lst(files, fd), 1);
	return (line);
}

char	*pick_a_line(char *file)
{
	char	*line;
	char	temp;
	int		nl;
	size_t	i;

	if (!file)
		return (NULL);
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
	line = join_line(0, file, 0);
	if (nl)
		file[i + 1] = temp;
	if (!line)
		free(file);
	return (line);
}

char	*trim_fst_line(char *file, char *smth, int mode)
{
	char	*new_file;
	size_t	i;

	if (mode)
	{
		free(smth);
		free(file);
		return (NULL);
	}
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
	new_file = join_line(0, &file[i], 0);
	free(file);
	return (new_file);
}
