/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_map_content_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 00:37:49 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/19 20:15:08 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

static int	comma_counter(char *s)
{
	char	*pos;
	int		i;

	i = 0;
	pos = NULL;
	pos = ft_strchr(s, ',');
	while (pos)
	{
		pos++;
		i++;
		pos = ft_strchr(pos, ',');
	}
	if (i != 2)
		return (printf("Wrong color commas format!\n"), 1);
	return (0);
}

static int	texture_checker(char **dest, char *id)
{
	char	*trimmed;
	char	*ext_pos;
	int		fd;

	if (!(*dest))
		return (printf("Texture for %s is missing!\n", id), 1);
	trimmed = ft_strtrim(*dest, " \n");
	freer(dest, 0);
	*dest = trimmed;
	ext_pos = ft_strnstr(*dest, ".xpm", ft_strlen(*dest));
	if (!ext_pos || *(ext_pos + 4) != '\0')
		return (printf("%s texture file format is not XPM!\n", id), 1);
	fd = open(*dest, O_RDONLY);
	if (fd < 0)
		return (printf("%s texture file can't be read!\n", id), 1);
	close(fd);
	return (0);
}

static int	color_checker(char **dest, int (*dest_arr)[3], char *id)
{
	char	**split;
	char	*buf;
	int		i;
	int		val;

	if (comma_counter(*dest))
		return (1);
	i = 0;
	split = ft_split(*dest, ',');
	if (!split)
		return (printf("Syscall error!\n"), 1);
	while (split[i] && i < 3)
	{
		buf = ft_strtrim(split[i], " \n");
		val = ft_safe_atoi(buf);
		if (val == -1)
			return (freer(&buf, &split), printf("Wrong %s colors!\n", id), 1);
		(*dest_arr)[i] = val;
		freer(&buf, 0);
		i++;
	}
	if (i == 3 && split[i])
		return (freer(0, &split), printf("Too many %s colors!\n", id), 1);
	freer(0, &split);
	return (0);
}

int	pre_map_content_checker(t_verif *v)
{
	if (texture_checker(&v->no, "NO"))
		return (1);
	if (texture_checker(&v->so, "SO"))
		return (1);
	if (texture_checker(&v->we, "WE"))
		return (1);
	if (texture_checker(&v->ea, "EA"))
		return (1);
	if (color_checker(&v->f, &v->f_arr, "F"))
		return (1);
	if (color_checker(&v->c, &v->c_arr, "C"))
		return (1);
	return (0);
}
