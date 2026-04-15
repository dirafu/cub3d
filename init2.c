#include "cub3d.h"

bool	ft_create_new_image(t_img_data *img_d, void *xconn, int x, int y)
{
	img_d->img = mlx_new_image(xconn, x, y);
	if (!img_d->img)
		return (false);
	img_d->addr = mlx_get_data_addr(img_d->img,
			&(img_d->bpp),
			&(img_d->size_line), &(img_d->endian));
	img_d->bytes_pp = img_d->bpp / 8;
	img_d->res_x = x;
	img_d->res_y = y;
	return (true);
}

bool	init_mouse(t_data *data)
{
	mlx_mouse_hide(data->x_data.xconn, data->x_data.win);
	mlx_mouse_move(data->x_data.xconn, data->x_data.win,
		data->x_data.res[0] / 2, data->x_data.res[1] / 2);
	return (true);
}

void	hook_up(t_data *data)
{
	mlx_hook(data->x_data.win, 2, 1L << 0, key_down, &data->input);
	mlx_hook(data->x_data.win, 3, 1L << 1, key_up, &data->input);
	mlx_hook(data->x_data.win, 17, 0, exit_handler, data);
	mlx_hook(data->x_data.win, 6, 1L << 6, handle_mouse, data);
	data->time_data.last_frame_time = ft_get_time_us();
	mlx_loop_hook(data->x_data.xconn, game_loop, data);
	mlx_loop(data->x_data.xconn);
}
