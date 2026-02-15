#include "cub3d.h"

void	rotate_player(t_player *player, float angle)
{
	player->dir = vec2d_rotate_by_angle(player->dir, angle);
	player->dir = vec2d_normalize(player->dir);
	player->cam_plane.y = -player->dir.x;
	player->cam_plane.x = player->dir.y;
	player->cam_plane = vec2d_mul(player->cam_plane, player->fov_scale);
}

t_point2d	set_step_and_radius(t_point2d *step, t_player *player, float step_size, enum direction dir)
{
	float		tmp;
	t_point2d	radius;

	*step = player->dir;
	if (dir == PERPENDICULAR)
	{
		tmp = -step->x;
		step->x = step->y;
		step->y = tmp;
	}
	*step = vec2d_mul(*step, ((step_size < 0) * -2 + 1));
	radius = vec2d_mul(*step, player->radius);
	*step = vec2d_mul(*step, 0.05f);
	return (radius);
}

void	step_player(t_player *player, char **map, float step_size, enum direction dir)
{
	t_point2d	step;
	t_point2d	new_pos;
	t_point2d	radius;

	radius = set_step_and_radius(&step, player, step_size, dir);
	step_size *= ((step_size < 0) * -2 + 1);
	while (step_size > 0)
	{
		step_size -= 0.05f;
		new_pos = vec2d_sum(player->pos, step);
		if (map[-((int)(new_pos.y + radius.y))][(int)(new_pos.x + radius.x)] == '1')
			return ;
		player->pos = new_pos;
	}
}
