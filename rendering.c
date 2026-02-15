#include "cub3d.h"

void	fill_render_info(t_render_facilities *rf,
		t_player *player, t_point2d *raydir)
{
	rf->hit = HIT_NONE;
	rf->x = player->pos.x;
	rf->y = player->pos.y;
	rf->t_x = 1 / (raydir->x * (((raydir->x < 0) * -2) + 1));
	rf->t_y = 1 / (raydir->y * (((raydir->y < 0) * -2) + 1));
	if (raydir->x < 0)
		rf->next_x = (player->pos.x - floorf(player->pos.x)) * rf->t_x;
	else
		rf->next_x = (floorf(player->pos.x) + 1 - player->pos.x) * rf->t_x;
	if (raydir->y < 0)
		rf->next_y = (player->pos.y - floorf(player->pos.y)) * rf->t_y;
	else
		rf->next_y = (floorf(player->pos.y) + 1 - player->pos.y) * rf->t_y;
	rf->step_x = ((raydir->x < 0) * -2) + 1;
	rf->step_y = ((raydir->y < 0) * -2) + 1;
	rf->overall_number_of_steps = 0;
	rf->tex_x = 0;
}

static void	do_step(t_point2d *raydir, t_render_facilities *rf)
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

void	cast_ray(t_data *data, t_point2d raydir, char **map, int x)
{
	t_render_facilities	rf;

	fill_render_info(&rf, &data->player, &raydir);
	while (rf.hit == HIT_NONE)
	{
		do_step(&raydir, &rf);
		rf.overall_number_of_steps++;
		// if (rf.overall_number_of_steps >= map.height + map.width)
		// 	return;
		if (map[-rf.y][rf.x] != '1')
			rf.hit = HIT_NONE;
	}
	if (rf.hit == HIT_EAST || rf.hit == HIT_WEST)
	{
		rf.wall_height = data->x_data.res[1] / (rf.next_x - rf.t_x);
		rf.tex_x = data->player.pos.y + raydir.y * (rf.next_x - rf.t_x);
	}
	else if (rf.hit == HIT_NORTH || rf.hit == HIT_SOUTH)
	{
		rf.wall_height = data->x_data.res[1] / (rf.next_y - rf.t_y);
		rf.tex_x = data->player.pos.x + raydir.x * (rf.next_y - rf.t_y);
	}
	rf.tex_x -= floorf(rf.tex_x);
	put_wall_bar_on_img(x, data, &rf);
}

void	draw_frame(t_data *data)
{
	int			x;
	t_x_data	*x_d;

	x_d = &(data->x_data);
	x = 0;
	while (x++ <= x_d->res[0])
	{
		cast_ray(data, vec2d_sum(data->player.dir,
				vec2d_mul(data->player.cam_plane,
					(float)x / x_d->res[0] * 2 - 1)), data->map, x);
	}
	mlx_put_image_to_window(x_d->xconn,
		x_d->win, x_d->curr_framebuf->img, 0, 0);
	mlx_do_sync(x_d->xconn);
	x_d->curr_framebuf = &(x_d->img_data[(x_d->framebuf_sel)++ % 2]);
}
