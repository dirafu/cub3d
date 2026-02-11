#include "cub3d.h"

void	put_px_on_img(t_x_data *x_data, int x, int y, int color)
{
	char			*addr_b;
	unsigned int	xcolor;

	if (x > 0 && x < x_data->res[0] && y > 0 && y < x_data->res[1])
	{
		xcolor = mlx_get_color_value(x_data->xconn, color);
		addr_b = (char *)(x_data->curr_framebuf->addr);
		addr_b += x_data->curr_framebuf->size_line * y
			+ x * (x_data->curr_framebuf->bpp / 8);
		*(unsigned int *)addr_b = xcolor;
	}
}

void	put_wall_bar_on_img(int x, int wall_height, int color, t_data *data)
{
	int	y;
	int	i;

	i = 0;
	y = (data->x_data.res[1] / 2) - wall_height / 2;
	while (i < y)
	{
		put_px_on_img(&data->x_data, x, i, data->ceiling_color);
		i++;
	}
	while (i < wall_height + y)
	{
		put_px_on_img(&data->x_data, x, i, color);
		i++;
	}
	while (i < data->x_data.res[1])
	{
		put_px_on_img(&data->x_data, x, i, data->floor_color);
		i++;
	}
}
