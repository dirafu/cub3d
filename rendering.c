#include "cub3d.h"

void	do_step(t_point2d *raydir, t_render_facilities *rf)
{
	if (rf->next_x < rf->next_y)
	{
		rf->next_x += rf->t_x;
		rf->x += rf->step_x;
		rf->hit = VERTICAL;
		if (raydir->x < 0)
			rf->hit = HIT_EAST;
		else
			rf->hit = HIT_WEST;
	}
	else
	{
		rf->next_y += rf->t_y;
		rf->y += rf->step_y;
		rf->hit = HORIZONTAL;
		if (raydir->y < 0)
			rf->hit = HIT_NORTH;
		else
			rf->hit = HIT_SOUTH;
	}
}

float	get_hit_dist(t_render_facilities *rf)
{
	float	hit_dist;

	hit_dist = 0;
	if (rf->hit == HIT_EAST || rf->hit == HIT_WEST)
		hit_dist = rf->next_x - rf->t_x;
	else if (rf->hit == HIT_NORTH || rf->hit == HIT_SOUTH)
		hit_dist = rf->next_y - rf->t_y;
	return (hit_dist);
}

void	cast_ray(t_data *data, t_point2d raydir, int x)
{
	t_render_facilities	rf;

	fill_render_info(&rf, &data->player, &raydir);
	while (rf.hit == HIT_NONE)
	{
		if (data->map[-rf.y][rf.x].type == CELL_DOOR
				&& draw_door(x, data, &rf, raydir))
			return ;
		do_step(&raydir, &rf);
		if (data->map[-rf.y][rf.x].type != CELL_WALL)
			rf.hit = HIT_NONE;
	}
	data->x_data.zbuff[x] = get_hit_dist(&rf);
	rf.wall_height = data->x_data.res[1] / data->x_data.zbuff[x];
	if (rf.hit == HIT_EAST || rf.hit == HIT_WEST)
		rf.tex_x = data->player.pos.y + raydir.y * (rf.next_x - rf.t_x);
	else if (rf.hit == HIT_NORTH || rf.hit == HIT_SOUTH)
		rf.tex_x = data->player.pos.x + raydir.x * (rf.next_y - rf.t_y);
	rf.tex_x -= floorf(rf.tex_x);
	put_wall_bar_on_img(x, data, &rf);
}

void	draw_walls(t_data *data)
{
	int			x;

	x = 0;
	while (x < data->x_data.res[0])
	{
		cast_ray(data, vec2d_sum(data->player.dir,
				vec2d_mul(data->player.cam_plane,
					(float)x / data->x_data.res[0] * 2 - 1)), x);
		x++;
	}
}

void	draw_frame(t_data *data)
{
	t_x_data	*x_d;

	x_d = &(data->x_data);
	draw_walls(data);
	switch_sprites_frames(&(data->time_data), data->sprites);
	draw_sprites(data);
	mlx_put_image_to_window(x_d->xconn,
		x_d->win, x_d->curr_framebuf->img, 0, 0);
	mlx_do_sync(x_d->xconn);
	x_d->curr_framebuf = &(x_d->img_data[(x_d->framebuf_sel)++ % 2]);
}
