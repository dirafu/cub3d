/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 01:25:34 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/19 20:16:58 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

int	ft_safe_atoi(const char *str)
{
	int	nb;

	if (str[0] == '0' && str[1] != '\0')
		return (printf("Color number starts from zero!\n"), -1);
	nb = 0;
	if (!str || !ft_isdigit(*str))
		return (-1);
	while (ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0');
		if (nb > 255)
			return (-1);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (nb);
}

void	freer(char **buf, char ***argv)
{
	int	i;

	i = 0;
	if (buf && *buf)
	{
		free(*buf);
		*buf = NULL;
	}
	if (argv && *argv)
	{
		while ((*argv)[i])
		{
			free((*argv)[i]);
			i++;
		}
		free(*argv);
		*argv = NULL;
	}
}

int	arg_check(char *argv)
{
	char	*ext_pos;

	ext_pos = NULL;
	if (argv[0] == '\0')
		return (1);
	if (ft_strlen(argv) <= 4)
		return (1);
	ext_pos = ft_strnstr(argv, ".cub", ft_strlen(argv));
	if (ext_pos == NULL)
		return (1);
	if (*(ext_pos + 4) != '\0')
		return (1);
	return (0);
}

void	struct_destroyer(t_verif *v)
{
	freer(&v->no, 0);
	freer(&v->so, 0);
	freer(&v->we, 0);
	freer(&v->ea, 0);
	freer(&v->f, 0);
	freer(&v->c, 0);
	freer(0, &v->map);
}

void	gnl_drain(int *fd)
{
	char	*line;

	line = get_next_line(*fd);
	while (line)
	{
		freer(&line, 0);
		line = get_next_line(*fd);
	}
}
