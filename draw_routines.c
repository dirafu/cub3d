#include "cub3d.h"

void	put_px_on_img(t_x_data *x_data, int x, int y, int color)
{
	char			*addr_b;
	unsigned int	xcolor;

	if (x > 0 && x < x_data->res[0] && y > 0 && y < x_data->res[1])
	{
		xcolor = mlx_get_color_value(x_data->xconn, color);
		addr_b = (char *)(x_data->addr);
		addr_b += x_data->size_line * y + x * (x_data->bpp / 8);
		*(unsigned int *)addr_b = xcolor;
	}
}