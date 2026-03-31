#include "cub3d.h"

int	handle_mouse(int x, int y, t_data *data)
{
	int			x_center;
	int			y_center;
	float		move_x;

	x_center = data->x_data.res[0] / 2;
	y_center = data->x_data.res[1] / 2;
	if (x == x_center && y == y_center)
		return (0);
	mlx_mouse_move(data->x_data.xconn, data->x_data.win,
		x_center, y_center);
	move_x = (double)(x - x_center) / data->x_data.res[0];
	rotate_player(&data->player, -move_x * 30);
	return (0);
}
