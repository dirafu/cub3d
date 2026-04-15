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
	rf->passed_door = NULL;
	rf->door_plate = false;
}

bool	draw_door_plate(int x, t_render_facilities *rf,
	float door_open_factor, t_data *data)
{
	rf->tex_x -= floorf(rf->tex_x);
	if (rf->tex_x > door_open_factor)
	{
		data->x_data.zbuff[x] = get_hit_dist(rf);
		rf->wall_height = data->x_data.res[1] / data->x_data.zbuff[x];
		rf->tex_x -= door_open_factor;
		rf->door_plate = true;
		return (put_wall_bar_on_img(x, data, rf), true);
	}
	return (false);
}

bool	draw_horizontal_door(int x, t_data *data,
	t_render_facilities rf, t_point2d raydir)
{
	rf.t_y /= 2;
	rf.next_y -= rf.t_y;
	do_step(&raydir, &rf);
	if (rf.hit == HIT_NORTH || rf.hit == HIT_SOUTH)
	{
		rf.tex_x = data->player.pos.x + raydir.x * (rf.next_y - rf.t_y);
		if (draw_door_plate(x, &rf,
				data->map[-rf.door_y][rf.door_x].door_open_factor, data))
			return (true);
	}
	return (false);
}

bool	draw_vertical_door(int x, t_data *data,
	t_render_facilities rf, t_point2d raydir)
{
	rf.t_x /= 2;
	rf.next_x -= rf.t_x;
	do_step(&raydir, &rf);
	if (rf.hit == HIT_WEST || rf.hit == HIT_EAST)
	{
		rf.tex_x = data->player.pos.y + raydir.y * (rf.next_x - rf.t_x);
		if (draw_door_plate(x, &rf,
				data->map[-rf.door_y][rf.door_x].door_open_factor, data))
			return (true);
	}
	return (false);
}

bool	draw_door(int x, t_data *data,
	t_render_facilities *rf_o, t_point2d raydir)
{
	rf_o->door_x = rf_o->x;
	rf_o->door_y = rf_o->y;
	if ((&(data->map[-rf_o->y][rf_o->x]))->door_orientation == HORIZONTAL)
	{
		if (draw_horizontal_door(x, data, *rf_o, raydir))
			return (true);
	}
	else
	{
		if (draw_vertical_door(x, data, *rf_o, raydir))
			return (true);
	}
	rf_o->passed_door = &(data->map[-rf_o->y][rf_o->x]);
	return (false);
}
