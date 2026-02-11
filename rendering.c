#include "cub3d.h"

void	fill_render_info(t_render_facilities *rf, t_player *player, t_point2d *raydir)
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
}

void	cast_ray(t_data *data, t_point2d raydir, char **map, int x)
{
	t_render_facilities	rf;

	fill_render_info(&rf, &data->player, &raydir);
	while (!rf.hit)
	{
		if (rf.next_x < rf.next_y)
		{
			rf.next_x += rf.t_x;
			rf.x += rf.step_x;
			rf.hit = VERTICAL;
		}
		else
		{
			rf.next_y += rf.t_y;
			rf.y += rf.step_y;
			rf.hit = HORIZONTAL;
		}
		if (map[-rf.y][rf.x] != '1')
			rf.hit = HIT_NONE;
	}
	if (rf.hit == VERTICAL)
		rf.wall_height = data->x_data.res[1] / (rf.next_x - rf.t_x);
	else if (rf.hit == HORIZONTAL)
		rf.wall_height = data->x_data.res[1] / (rf.next_y - rf.t_y);
	put_wall_bar_on_img(x, rf.wall_height, (255 << 8) + (255 << 16), &data->x_data);
}

void	draw_frame(t_data *data)
{
	int	x;

	ft_bzero(data->x_data.addr, data->x_data.res[0] * data->x_data.res[1] * (data->x_data.bpp / 8));
	x = 0;
	while (x++ <= data->x_data.res[0])
	{
		cast_ray(data, vec2d_sum(data->player.dir,
			vec2d_mul(data->player.cam_plane, (float)x / data->x_data.res[0] * 2 - 1)), data->map, x);
	}
	mlx_put_image_to_window(data->x_data.xconn, data->x_data.win, data->x_data.img, 0, 0);
}
