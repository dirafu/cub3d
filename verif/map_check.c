/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 02:30:15 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/12 02:28:44 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

static int	map_copier(t_verif *v, char *s, size_t n)
{
	int		i;
	char	*buf;

	i = 0;
	v->map[n] = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!v->map[n])
		return (printf("Syscall error!\n"), 1);
	while (s[i] == ' ')
		v->map[n][i++] = ' ';
	buf = ft_strtrim(s, " \n");
	if (!buf)
		return (printf("Syscall error!\n"), 1);
	if (map_char_checker(v, buf, &i, n))
		return (freer(&buf, 0), 1);
	return (freer(&buf, 0), v->map[n][i] = '\0', 0);
}

static int	map_creator(t_verif *v, int *fd)
{
	char	*line;
	size_t	row_count;

	row_count = 0;
	line = get_next_line(*fd);
	if (!line)
		return (printf("Empty map!\n"), 1);
	while (line[0] == '\n')
	{
		freer(&line, 0);
		line = get_next_line(*fd);
	}
	while (line)
	{
		if (line[0] == '\n')
			return (printf("Empty line in map!\n"), freer(&line, 0), 1);
		if (ft_realloc(&v->map, row_count))
			return (freer(&line, 0), 1);
		if (map_copier(v, line, row_count))
			return (freer(&line, 0), 1);
		freer(&line, 0);
		line = get_next_line(*fd);
		row_count++;
	}
	return (v->map[row_count] = NULL, 0);
}

int static	first_last_row_check(char *row)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(row);
	while (i < len)
	{
		if (row[i] != '1' && row[i] != ' ')
			return (printf("Map's top or bottom edge is open!\n"), 1);
		i++;
	}
	return (0);
}

int static	edge_case_checker(t_verif *v)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (first_last_row_check(v->map[0]))
		return (1);
	if (first_last_row_check(v->map[v->rows - 1]))
		return (1);
	while (v->map[i])
	{
		j = 0;
		while (v->map[i][j] == ' ')
			j++;
		if (v->map[i][j] != '1')
			return (printf("Left edge is open!\n"), 1);
		while (v->map[i][j + 1])
			j++;
		if (v->map[i][j] != '1')
			return (printf("Right edge is open!\n"), 1);
		i++;
	}
	return (0);
}

int	map_check(t_verif *v, int *fd)
{
	if (map_creator(v, fd))
		return (1);
	if (v->orient == '\0')
		return (printf("Player token is missing!\n"), 1);
	v->rows = row_counter(v->map);
	if (v->rows < 3)
		return (printf("Map too small\n"), 1);
	if (edge_case_checker(v))
		return (1);
	if (row_checker(v->map))
		return (1);
	v->cols = col_counter(v->map);
	return (0);
}
