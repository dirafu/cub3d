#include "cub3d.h"
void	draw_door_plate(int x, t_render_facilities *rf, float door_open_factor, t_data *data)
{
	int			y;
	int			i;
	int			wall_y;

	i = 0;
	y = (data->x_data.res[1] / 2) - rf->wall_height / 2;
	while (i < y && ++i)
		put_px_on_img(&data->x_data, x, i - 1, data->ceiling_color);
	if (y < 0)
		wall_y = -y;
	else
		wall_y = 0;
	rf->tex_x -= door_open_factor;
	while (i < rf->wall_height + y && ++i)
	{
		put_px_on_img(&data->x_data, x, i - 1, get_texture_pixel(wall_y, data, rf, &data->door_textures[DOOR_TEX_FACE]));
		wall_y++;
	}
	while (i < data->x_data.res[1] && ++i)
		put_px_on_img(&data->x_data, x, i - 1, data->floor_color);
}

bool	draw_horizontal_door(int x, t_data *data, t_render_facilities rf, t_point2d raydir)
{
	rf.t_y /= 2;
	rf.next_y -= rf.t_y;
	do_step(&raydir, &rf);
	if (rf.hit == HIT_NORTH || rf.hit == HIT_SOUTH)
	{
		rf.tex_x = data->player.pos.x + raydir.x * (rf.next_y - rf.t_y);
		rf.tex_x -= floorf(rf.tex_x);
		if (rf.tex_x > data->map[-rf.door_y][rf.door_x].door_open_factor)
		{
			data->x_data.zbuff[x] = get_hit_dist(&rf);
			rf.wall_height = data->x_data.res[1] / data->x_data.zbuff[x];
			return (draw_door_plate(x, &rf, data->map[-rf.door_y][rf.door_x].door_open_factor, data), true);
		}
	}
	return (false);
}

bool	draw_vertical_door(int x, t_data *data, t_render_facilities rf, t_point2d raydir)
{
	rf.t_x /= 2;
	rf.next_y -= rf.t_x;
	do_step(&raydir, &rf);
	if (rf.hit == HIT_WEST || rf.hit == HIT_EAST)
	{
		rf.tex_x = data->player.pos.y + raydir.y * (rf.next_x - rf.t_x);
		rf.tex_x -= floorf(rf.tex_x);
		if (rf.tex_x > data->map[-rf.door_y][rf.door_x].door_open_factor)
		{
			data->x_data.zbuff[x] = get_hit_dist(&rf);
			rf.wall_height = data->x_data.res[1] / data->x_data.zbuff[x];
			return (draw_door_plate(x, &rf, data->map[-rf.door_y][rf.door_x].door_open_factor, data), true);
		}
	}
	return (false);
}

bool	draw_door(int x, t_data *data, t_render_facilities *rf_o, t_point2d raydir)
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
