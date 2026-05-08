/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 02:55:21 by ikiriush          #+#    #+#             */
/*   Updated: 2026/05/08 04:34:07 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	draw_bg(t_data *data)
{
	int	i;
	int	offset;

	i = 0;
	while (i < data->mm.size_y)
	{
		offset = (i + data->mm.offset_y + data->mm.diff_y)
			* data->x_data.curr_framebuf->size_line
			+ (data->mm.offset_x + data->mm.diff_x) * data->mm.byte_pp;
		ft_memset
			(data->x_data.curr_framebuf->addr + offset,
			0,
			data->mm.tile_px * TILE_X * data->mm.byte_pp);
		i++;
	}
}

void	draw_tiles(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = (int)data->player.pos.x;
	y = (int)data->player.pos.y * (-1);
	i = -1;
	while (++i < data->verif->rows)
	{
		j = -1;
		while (++j < data->verif->cols)
		{
			if (data->map[i][j].type == CELL_TERMINATOR)
				break ;
			if ((j >= x - SPAN_X && j <= x + SPAN_X)
				&& (i >= y - SPAN_Y && i <= y + SPAN_Y))
			{
				if (data->map[i][j].type == CELL_WALL)
					draw_tile(data, i - y + SPAN_Y, j - x + SPAN_X, 0x99);
				else if (data->map[i][j].type != CELL_NONE)
					draw_tile(data, i - y + SPAN_Y, j - x + SPAN_X, 0xFF);
			}
		}
	}
}

void	draw_player(t_data *data)
{
	int		r;	
	float	rad;
	float	frac_x;
	float	frac_y;

	frac_x = data->player.pos.x - (int)data->player.pos.x;
	frac_y = data->player.pos.y - (int)data->player.pos.y;
	r = data->mm.tile_px / 3;
	rad = 0;
	while (r > 0)
	{
		while (rad < 2 * PI)
		{
			put_px_on_img(&(data->x_data),
				data->mm.offset_x + data->mm.diff_x + data->mm.tile_px * SPAN_X
				+ (int)(frac_x * data->mm.tile_px) + cos(rad) * r,
				data->mm.offset_y + data->mm.diff_y + data->mm.tile_px * SPAN_Y
				- (int)(frac_y * data->mm.tile_px) + sin(rad) * r,
				0xff64ffa4);
			rad = rad + 0.01;
		}
		r--;
		rad = 0;
	}
}

void	draw_tile(t_data *data, int i, int j, int color)
{
	int		k;
	int		offset_y_mm;
	int		offset_x_mm;
	int		x;
	int		y;

	k = 0;
	x = j + (int)data->player.pos.x - SPAN_X;
	y = i - (int)data->player.pos.y - SPAN_Y;
	while (k < data->mm.tile_px - 1)
	{
		offset_x_mm = (data->mm.offset_x + data->mm.diff_x + data->mm.tile_px
				* j) * data->mm.byte_pp;
		offset_y_mm = (data->mm.offset_y + data->mm.diff_y + data->mm.tile_px
				* i + k) * data->x_data.curr_framebuf->size_line;
		if (data->map[y][x].type == CELL_DOOR
			&& data->map[y][x].door_status == 0)
			color = color + 0x55;
		ft_memset
			(data->x_data.curr_framebuf->addr + offset_x_mm + offset_y_mm,
			color,
			data->mm.tile_px * data->mm.byte_pp - 4);
		k++;
	}
}
