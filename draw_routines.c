#include "cub3d.h"

void	put_px_on_img(t_x_data *x_data, int x, int y, int color)
{
	char			*addr_b;
	unsigned int	xcolor;

	if (x >= 0 && x < x_data->res[0] && y >= 0 && y < x_data->res[1])
	{
		xcolor = mlx_get_color_value(x_data->xconn, color);
		addr_b = (char *)(x_data->curr_framebuf->addr);
		addr_b += x_data->curr_framebuf->size_line * y
			+ x * (x_data->curr_framebuf->bpp / 8);
		*(unsigned int *)addr_b = xcolor;
	}
}

int		get_img_px_color(t_img_data *image, int x, int y)
{
	int		color;

	color = 0;
	if (image)
		color = *((unsigned int *)(image->addr +
			y * image->size_line + x * image->bpp / 8));
	return (color);
}

int	get_texture_pixel(int wall_y, t_data *data, t_render_facilities *rf)
{
	int	x;
	int	y;

	x = rf->tex_x * data->textures[rf->hit].res_x;
	y = (float)wall_y / rf->wall_height * data->textures[rf->hit].res_y;
	return (get_img_px_color(&data->textures[rf->hit], x, y));
}

void	put_wall_bar_on_img(int x, t_data *data, t_render_facilities *rf)
{
	int	y;
	int	i;
	int	wall_y;

	i = 0;
	wall_y = 0;
	y = (data->x_data.res[1] / 2) - rf->wall_height / 2;
	while (i < y)
	{
		put_px_on_img(&data->x_data, x, i, data->ceiling_color);
		i++;
	}
	while (i < rf->wall_height + y)
	{
		put_px_on_img(&data->x_data, x, i, get_texture_pixel(wall_y, data, rf));
		i++;
		wall_y++;
	}
	while (i < data->x_data.res[1])
	{
		put_px_on_img(&data->x_data, x, i, data->floor_color);
		i++;
	}
}
