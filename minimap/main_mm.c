/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 01:53:25 by ikiriush          #+#    #+#             */
/*   Updated: 2026/05/06 04:10:30 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	draw_minimap_main(t_data *data)
{
	data->mm.size_x = MM_SCALE * data->x_data.res[0];
	data->mm.size_y = MM_SCALE * data->x_data.res[1];
	data->mm.offset_x = (1 - MM_SCALE) * data->x_data.res[0];
	data->mm.offset_y = (1 - MM_SCALE) * data->x_data.res[1];
	data->mm.byte_pp = data->x_data.curr_framebuf->bpp / 8;
	data->mm.tile_px = MIN(data->mm.size_x / TILE_X, data->mm.size_y / TILE_Y);
	draw_bg(data);
	draw_tiles(data);
	draw_player(data);
	cast_mm_cone(data);
}
