/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_mm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <vlchinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 01:22:49 by ikiriush          #+#    #+#             */
/*   Updated: 2026/05/08 19:12:26 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

static void	put_px_ray(t_data *data, float x, float y)
{
	float	frac_x;
	float	frac_y;

	frac_x = data->player.pos.x - (int)data->player.pos.x;
	frac_y = data->player.pos.y - (int)data->player.pos.y;
	put_px_on_img(&(data->x_data),
		data->mm.offset_x + data->mm.diff_x + data->mm.tile_px * SPAN_X
		+ (int)(frac_x * data->mm.tile_px)
		+ (x - data->player.pos.x) * data->mm.tile_px,
		data->mm.offset_y + data->mm.diff_y + data->mm.tile_px * SPAN_Y
		- (int)(frac_y * data->mm.tile_px)
		+ (y - data->player.pos.y) * (-1) * data->mm.tile_px,
		0xffe580ff);
}

static int	check_adj(t_data *data, float x, float y)
{
	int	i;
	int	j;

	j = (int)x;
	i = (int)y * (-1);
	if (data->map[i][j].type == CELL_WALL
			|| (data->map[i][j].type == CELL_DOOR
			&& data->map[i][j].door_status == 0)
			|| data->map[i][j].type == CELL_TERMINATOR
			|| data->map[i][j].type == CELL_NONE)
		return (1);
	return (0);
}

static void	cast_mm_ray(t_data *data, float t)
{
	float	x;
	float	y;
	int		i;
	int		j;

	x = data->player.pos.x;
	y = data->player.pos.y;
	j = (int)x;
	i = (int)y * (-1);
	while (data->map[i][j].type != CELL_TERMINATOR
		&& data->map[i][j].type != CELL_NONE)
	{
		x = x + (data->player.dir.x + data->player.cam_plane.x * t) * 0.01f;
		y = y + (data->player.dir.y + data->player.cam_plane.y * t) * 0.01f;
		j = (int)x;
		i = (int)y * (-1);
		if (check_adj(data, x, y) || check_adj(data, x + 0.01, y - 0.01)
			|| check_adj(data, x - 0.01, y + 0.01)
			|| check_adj(data, x + 0.01, y + 0.01)
			|| check_adj(data, x - 0.01, y - 0.01))
			break ;
		if (ft_abs(i + (int)data->player.pos.y) <= SPAN_Y
			&& ft_abs(j - (int)data->player.pos.x) <= SPAN_X)
			put_px_ray(data, x, y);
	}
}

void	cast_mm_cone(t_data *data)
{
	float	t;

	t = -1.0;
	while (t < 1.0)
	{
		cast_mm_ray(data, t);
		t = t + 0.01f;
	}
}
