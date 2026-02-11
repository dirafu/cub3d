#include "cub3d.h"

void	rotate_player(t_player *player, float angle)
{
	player->dir = vec2d_rotate_by_angle(player->dir, angle);
	player->dir = vec2d_normalize(player->dir);
	player->cam_plane.y = -player->dir.x;
	player->cam_plane.x = player->dir.y;
	player->cam_plane = vec2d_mul(player->cam_plane, player->fov_scale);
}

void	step_player(t_player *player, float step_size, enum direction dir)
{
	t_point2d	step;
	float		tmp;

	step = player->dir;
	if (dir == PERPENDICULAR)
	{
		tmp = -step.x;
		step.x = step.y;
		step.y = tmp;
	}
	step = vec2d_mul(step, step_size);
	player->pos = vec2d_sum(player->pos, step);
}
