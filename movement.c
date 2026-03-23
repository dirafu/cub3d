#include "cub3d.h"

void	rotate_player(t_player *player, float angle)
{
	player->dir = vec2d_rotate_by_angle(player->dir, angle);
	player->dir = vec2d_normalize(player->dir);
	player->cam_plane.y = -player->dir.x;
	player->cam_plane.x = player->dir.y;
	player->cam_plane = vec2d_mul(player->cam_plane, player->fov_scale);
}

t_point2d	get_direction(t_point2d player_dir, enum direction dir)
{
	float	tmp;

	if (dir == PERPENDICULAR)
	{
		tmp = -player_dir.x;
		player_dir.x = player_dir.y;
		player_dir.y = tmp;
	}
	return (player_dir);
}

void	step_player(t_player *player, t_map **map, float step_size, enum direction dir)
{
	t_point2d	step;
	t_point2d	new_pos;
	t_point2d	radius;
	int			sign;

	sign = ((step_size < 0) * -2 + 1);
	step = get_direction(player->dir, dir);
	step = vec2d_mul(step, sign);
	radius = vec2d_mul(step, player->radius);
	step = vec2d_mul(step, 0.05f);
	step_size *= sign;
	while (step_size > 0)
	{
		step_size -= 0.05f;
		new_pos = vec2d_sum(player->pos, step);
		if (map[-((int)(new_pos.y + radius.y))][(int)(new_pos.x + radius.x)].type == CELL_WALL)
			return ;
		player->pos = new_pos;
	}
}
