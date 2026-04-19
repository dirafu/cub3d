/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 22:30:16 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/12 02:30:05 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

int	map_char_checker(t_verif *v, char *buf, int *i, int n)
{
	while (*buf)
	{
		if (*buf == 'N' || *buf == 'S' || *buf == 'W' || *buf == 'E')
		{
			if (v->orient)
				return (printf("More than 1 player token!\n"), 1);
			v->orient = *buf;
			v->pos_x = *i;
			v->pos_y = n;
		}
		else if (*buf != '0' && *buf != '1' && *buf != ' '
			&& *buf != 'D' && *buf != 's' && *buf != 'o')
			return (printf("Invalid map character: %c!\n", *buf), 1);
		v->map[n][(*i)++] = *buf++;
	}
	return (0);
}

int	ft_realloc(char ***ptr, size_t old_size)
{
	void	*new;

	if (old_size == 0)
	{
		*ptr = ft_calloc(sizeof(char *), 2);
		if (!ptr)
			return (printf("Syscall failure!\n"), 1);
		return (0);
	}
	new = ft_calloc(sizeof(char *), old_size + 2);
	if (!new)
		return (printf("Syscall failure!\n"), 1);
	ft_memcpy(new, *ptr, old_size * sizeof(char *));
	free(*ptr);
	*ptr = new;
	return (0);
}

int	row_counter(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	col_counter(char **map)
{
	int	i;
	int	max;
	int	curr;

	i = 1;
	max = ft_strlen(map[0]);
	while (map[i])
	{
		curr = ft_strlen(map[i]);
		if (curr > max)
			max = curr;
		i++;
	}
	return (max);
}

int	space_zero_crosscheker(char **map, int i, int j)
{
	if (map[i][j - 1] == '0'
		|| map[i - 1][j] == '0'
		|| map[i][j + 1] == '0'
		|| map[i + 1][j] == '0')
	{
		printf("Void is exposed!\n");
		return (1);
	}
	return (0);
}
