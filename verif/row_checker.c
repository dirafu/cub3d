/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 04:12:50 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/09 23:16:22 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

static int	v_door_check(char **map, int i, int j)
{
	if (map[i - 1][j] == '1')
	{
		if (map[i + 1][j] != '1')
			return (printf("Doors must be between walls!\n"), 1);
	}
	if (map[i + 1][j] == '1')
	{
		if (map[i - 1][j] != '1')
			return (printf("Doors must be between walls!\n"), 1);
	}
	return (0);
}

static int	h_door_check(char **map, int i, int j)
{
	if (map[i][j - 1] == '1')
	{
		if (map[i][j + 1] != '1')
			return (printf("Doors must be between walls!\n"), 1);
	}
	if (map[i][j + 1] == '1')
	{
		if (map[i][j - 1] != '1')
			return (printf("Doors must be between walls!\n"), 1);
	}
	return (0);
}

int	door_checker(char **map, int i, int j)
{
	int	c;

	c = 0;
	if (map[i][j - 1] == '1')
		c++;
	if (map[i][j + 1] == '1')
		c++;
	if (map[i - 1][j] == '1')
		c++;
	if (map[i + 1][j] == '1')
		c++;
	if (c < 2)
		return (printf("Doors must be between walls!\n"), 1);
	if (c > 2)
		return (printf("Doors must be between places!\n"), 1);
	if (v_door_check(map, i, j) || h_door_check(map, i, j))
		return (1);
	return (0);
}

int	row_checker(char **map)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (map[i + 1])
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] == ' ' && (j != 0 && j != ft_strlen(map[i]) - 1))
				&& space_zero_crosscheker(map, i, j))
				return (1);
			if ((j > ft_strlen(map[i - 1]) - 1
					|| (map[i + 1] && j > ft_strlen(map[i + 1]) - 1))
				&& map[i][j] != '1')
				return (printf("Out-of-bounds map portion has gaps!"), 1);
			if (map[i][j] == 'D' && door_checker(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
