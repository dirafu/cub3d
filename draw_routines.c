#include "cub3d.h"

void	put_px_on_img(t_x_data *x_data, int x, int y, int color)
{
	char			*addr_b;

	if (x >= 0 && x < x_data->res[0] && y >= 0 && y < x_data->res[1])
	{
		addr_b = (char *)(x_data->curr_framebuf->addr);
		addr_b += x_data->curr_framebuf->size_line * y
			+ x * (x_data->curr_framebuf->bpp / 8);
		*(unsigned int *)addr_b = color;
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

int	get_texture_pixel(int wall_y, t_data *data, t_render_facilities *rf, t_img_data *tx)
{
	int	x;
	int	y;

	x = rf->tex_x * data->wall_textures[rf->hit].res_x;
	y = (float)wall_y / rf->wall_height * tx->res_y;
	return (get_img_px_color(tx, x, y));
}

static t_img_data *set_tx(t_data *data, t_render_facilities *rf)
{
	t_img_data *tx;

	tx = &data->wall_textures[rf->hit];
	if (rf->door_plate)
		tx = &data->door_textures[DOOR_TEX_FACE];
	else if (rf->passed_door)
	{
		if ((rf->passed_door->door_orientation == HORIZONTAL
			&& ft_abs(rf->x - rf->door_x) == 1
			&& rf->y == rf->door_y)
			|| (rf->passed_door->door_orientation == VERTICAL
			&& ft_abs(rf->y - rf->door_y) == 1
			&& rf->x == rf->door_x))
			tx = &data->door_textures[DOOR_TEX_SIDE];
	}
	return (tx);
}

void	put_wall_bar_on_img(int x, t_data *data, t_render_facilities *rf)
{
	int			y;
	int			i;
	int			wall_y;
	t_img_data *tx;

	tx = set_tx(data, rf);
	i = 0;
	y = (data->x_data.res[1] / 2) - rf->wall_height / 2;
	while (i < y && ++i)
		put_px_on_img(&data->x_data, x, i - 1, data->ceiling_color);
	if (y < 0)
		wall_y = -y;
	else
		wall_y = 0;
	while (i < rf->wall_height + y && ++i)
	{
		put_px_on_img(&data->x_data, x, i - 1, get_texture_pixel(wall_y, data, rf, tx));
		wall_y++;
	}
	while (i < data->x_data.res[1] && ++i)
		put_px_on_img(&data->x_data, x, i - 1, data->floor_color);
}
