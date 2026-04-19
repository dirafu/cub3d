/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_map_structure_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:52:25 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/19 20:16:28 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

static int	pre_map_str_extractor(char *id, char ***split, char *s, char **dest)
{
	size_t	full_len;
	size_t	id_len;
	size_t	pref_len;
	char	*pos;

	id_len = ft_strlen(id);
	pref_len = ft_strlen((*split)[0]);
	if (pref_len < id_len)
		return (1);
	if (!ft_strncmp((*split)[0], id, pref_len) && !(*dest))
	{
		full_len = ft_strlen(s);
		pos = ft_strnstr(s, id, full_len);
		if (pos)
			*dest = ft_strdup(pos + pref_len + 1);
		else
			return (1);
		return (freer(0, split), 0);
	}
	return (1);
}

static int	pre_map_pending(t_verif *v)
{
	if (!v->no || !v->so || !v->we || ! v->ea || !v->f || !v->c)
		return (1);
	return (0);
}

static int	pre_map_parse(char *s, t_verif *p)
{
	char	**sp;

	sp = ft_split (s, ' ');
	if (!sp)
		return (printf("Syscall error!\n"), 1);
	if (!sp[0] || (sp[0] && !sp[1]))
		return (printf("Premap field incomplete: %s", sp[0]), freer(0, &sp), 1);
	if (sp[0][0] == '\n')
		return (freer(0, &sp), 0);
	if (!pre_map_str_extractor("NO", &sp, s, &p->no))
		return (0);
	else if (!pre_map_str_extractor("SO", &sp, s, &p->so))
		return (0);
	else if (!pre_map_str_extractor("WE", &sp, s, &p->we))
		return (0);
	else if (!pre_map_str_extractor("EA", &sp, s, &p->ea))
		return (0);
	else if (!pre_map_str_extractor("C", &sp, s, &p->c))
		return (0);
	else if (!pre_map_str_extractor("F", &sp, s, &p->f))
		return (0);
	return (freer(0, &sp), 1);
}

static int	pre_map_validator(int *fd, t_verif *v)
{
	char	*line;

	line = get_next_line(*fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			if (pre_map_parse(line, v))
			{
				printf("No matches in pre-map content!\n");
				return (freer(&line, 0), 1);
			}
		}
		freer(&line, 0);
		if (pre_map_pending(v))
			line = get_next_line(*fd);
	}
	if (pre_map_pending(v))
	{
		printf("Pre-map data incomplete\n");
		return (freer(&line, 0), 1);
	}
	return (freer(&line, 0), 0);
}

int	pre_map_structure_checker(char *argv, t_verif *v, int *fd)
{
	*fd = open(argv, O_RDONLY);
	if (*fd < 0)
	{
		printf("Map file doesn't exist or can't be read\n");
		return (1);
	}
	if (pre_map_validator(fd, v))
		return (gnl_drain(fd), 1);
	return (0);
}
