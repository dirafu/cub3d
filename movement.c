#include "cub3d.h"

void	rotate_player(t_player *player, float angle)
{
	player->dir = vec2d_rotate_by_angle(player->dir, angle);
	player->dir = vec2d_normalize(player->dir);
	player->cam_plane.y = -player->dir.x;
	player->cam_plane.x = player->dir.y;
	player->cam_plane_normalized = player->cam_plane;
	player->cam_plane = vec2d_mul(player->cam_plane, player->fov_scale);
	player->angle_rad = atan2f(player->dir.y, player->dir.x);
	if (player->angle_rad < 0)
		player->angle_rad += M_PI * 2;
}

static t_point2d	get_direction(t_point2d player_dir, enum e_direction dir)
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

static bool	step_x(t_point2d *new_pos, t_point2d step,
	t_map **map, t_point2d radius)
{
	t_map		*step_cell;
	t_point2d	test_pos;

	test_pos = *new_pos;
	test_pos.x += step.x;
	step_cell = &map[-((int)(test_pos.y + radius.y))]
	[(int)(test_pos.x + radius.x)];
	if (step_cell->type == CELL_WALL
		|| (step_cell->type == CELL_DOOR
			&& step_cell->door_status != DOOR_STATUS_OPENED))
		return (false);
	*new_pos = test_pos;
	return (true);
}

static bool	step_y(t_point2d *new_pos, t_point2d step,
	t_map **map, t_point2d radius)
{
	t_map		*step_cell;
	t_point2d	test_pos;

	test_pos = *new_pos;
	test_pos.y += step.y;
	step_cell = &map[-((int)(test_pos.y + radius.y))]
	[(int)(test_pos.x + radius.x)];
	if (step_cell->type == CELL_WALL
		|| (step_cell->type == CELL_DOOR
			&& step_cell->door_status != DOOR_STATUS_OPENED))
		return (false);
	*new_pos = test_pos;
	return (true);
}

void	step_player(t_player *player, t_map **map,
	float step_size, enum e_direction dir)
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
		new_pos = player->pos;
		if (!step_x(&new_pos, step, map, radius)
			& !step_y(&new_pos, step, map, radius))
			return ;
		player->pos = new_pos;
	}
}
