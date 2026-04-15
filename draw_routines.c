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

static t_img_data	*set_tx(t_data *data, t_render_facilities *rf)
{
	t_img_data	*tx;

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

void	put_bg(t_wall_draw_ctx *ctx, int bound, int color)
{
	while (ctx->i < bound)
	{
		*(unsigned int *)(ctx->buff) = color;
		ctx->buff += ctx->size_line;
		(ctx->i)++;
	}
}

void	put_wall(t_wall_draw_ctx *ctx,
	t_render_facilities *rf, int wall_y, int y)
{
	int		tx_x;
	int		bound;
	char	*tx_buff;
	float	y_step;
	float	y_acc;

	tx_x = rf->tex_x * ctx->tx->res_x;
	y_step = (float)ctx->tx->res_y / rf->wall_height;
	y_acc = wall_y * y_step;
	tx_buff = (char *)(ctx->tx->addr) + tx_x * ctx->tx->bytes_pp
		+ (ctx->tx->size_line * (int)y_acc);
	bound = rf->wall_height + y;
	if (bound > ctx->x_data->res[1])
		bound = ctx->x_data->res[1];
	while (ctx->i < bound)
	{
		*(unsigned int *)(ctx->buff) = *(unsigned int *)tx_buff;
		ctx->buff += ctx->size_line;
		if ((int)y_acc != (int)(y_acc + y_step))
			tx_buff += ((int)(y_acc + y_step)
					- (int)y_acc) * ctx->tx->size_line;
		y_acc += y_step;
		(ctx->i)++;
	}
}

void	put_wall_bar_on_img(int x, t_data *data, t_render_facilities *rf)
{
	int				y;
	int				wall_y;
	t_wall_draw_ctx	ctx;

	ctx.buff = (char *)(data->x_data.curr_framebuf->addr)
		+ x * data->x_data.curr_framebuf->bytes_pp;
	ctx.i = 0;
	ctx.x_data = &data->x_data;
	ctx.tx = set_tx(data, rf);
	ctx.size_line = data->x_data.curr_framebuf->size_line;
	y = (data->x_data.res[1] / 2) - rf->wall_height / 2;
	if (y < 0)
		wall_y = -y;
	else
	{
		put_bg(&ctx, y, data->ceiling_color);
		wall_y = 0;
	}
	put_wall(&ctx, rf, wall_y, y);
	put_bg(&ctx, data->x_data.res[1], data->floor_color);
}
