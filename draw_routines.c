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

int	get_img_px_color(t_img_data *image, int x, int y)
{
	int		color;

	color = 0;
	if (image)
		color = *((unsigned int *)(image->addr
					+ y * image->size_line + x * image->bpp / 8));
	return (color);
}

int	get_texture_pixel(int wall_y, t_render_facilities *rf, t_img_data *tx)
{
	int	x;
	int	y;

	x = rf->tex_x * tx->res_x;
	y = (float)wall_y / rf->wall_height * tx->res_y;
	return (get_img_px_color(tx, x, y));
}
