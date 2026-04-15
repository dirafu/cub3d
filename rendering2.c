#include "cub3d.h"

void	put_sprite_on_img_pt3(float tx_xy[2], int img_xy[2],
	t_data *data, t_sprite_rendering_view *r_v)
{
	int	color;

	if ((img_xy[0] < 0 || img_xy[0] > data->x_data.res[0])
		|| (img_xy[1] < 0 || img_xy[1] > data->x_data.res[1])
		|| r_v->pos_tr.y >= data->x_data.zbuff[img_xy[0]])
		return ;
	color = get_img_px_color(
			&(r_v->sprite->animation->frames[r_v->sprite->curr_frame]),
			tx_xy[0], tx_xy[1]);
	if (color != 0x980088)
		put_px_on_img(&(data->x_data), img_xy[0], img_xy[1], color);
}

void	cull_non_visible(t_sprite_draw_ctx *ctx)
{
	if (ctx->img_xy[0] < 0)
	{
		ctx->tx_xy[0] += ctx->step_xy[0] * (-ctx->img_xy[0]);
		ctx->proj_res[0] += ctx->img_xy[0];
		ctx->img_xy[0] = 0;
	}
	if (ctx->img_xy[1] < 0)
	{
		ctx->tx_xy[1] += ctx->step_xy[1] * (-ctx->img_xy[1]);
		ctx->proj_res[1] += ctx->img_xy[1];
		ctx->img_xy[1] = 0;
	}
	if ((ctx->img_xy[0] + ctx->proj_res[0]) > ctx->x_data->res[0])
		ctx->proj_res[0] = ctx->x_data->res[0] - ctx->img_xy[0];
	if ((ctx->img_xy[1] + ctx->proj_res[1]) > ctx->x_data->res[1])
		ctx->proj_res[1] = ctx->x_data->res[1] - ctx->img_xy[1];
}

void	put_sprite_on_img_pt2(t_sprite_draw_ctx	*ctx)
{
	while (ctx->proj_res[0]-- && ++ctx->img_xy[0])
	{
		ctx->tx_xy[1] = ctx->tx_y;
		ctx->proj_res[1] = ctx->proj_res_y;
		ctx->fr_buff_rst = ctx->fr_buff;
		ctx->tx_buff_rst = ctx->tx_buff;
		while (ctx->proj_res[1]-- && ctx->sp_z
			< ctx->x_data->zbuff[ctx->img_xy[0] - 1])
		{
			if (*(unsigned int *)ctx->tx_buff != 0x980088)
				*(unsigned int *)ctx->fr_buff = *(unsigned int *)ctx->tx_buff;
			ctx->fr_buff += ctx->fr_size_line;
			if ((int)ctx->tx_xy[1] != ctx->tx_xy[1] + ctx->step_xy[1])
				ctx->tx_buff += ((int)(ctx->tx_xy[1] + ctx->step_xy[1])
						- (int)ctx->tx_xy[1]) * ctx->tx_size_line;
			ctx->tx_xy[1] += ctx->step_xy[1];
		}
		ctx->tx_buff = ctx->tx_buff_rst;
		ctx->fr_buff = ctx->fr_buff_rst;
		if ((int)ctx->tx_xy[0] != ctx->tx_xy[0] + ctx->step_xy[0])
			ctx->tx_buff += ((int)(ctx->tx_xy[0] + ctx->step_xy[0])
					- (int)ctx->tx_xy[0]) * ctx->tx->bytes_pp;
		ctx->fr_buff += ctx->x_data->curr_framebuf->bytes_pp;
		ctx->tx_xy[0] += ctx->step_xy[0];
	}
}

//proj_res is sprite's resolution in screen space (projected)
//proj_res[0] is width
//proj_res[1] is height
//img_xy is sprite's left upper coordinates in screen space
//img_xy[0] is x
//img_xy[1] is y
void	put_sprite_on_img(t_data *data, t_sprite_rendering_view *r_v)
{
	t_sprite_draw_ctx	ctx;

	ctx.x_data = &data->x_data;
	ctx.proj_res[0] = r_v->p_res[0];
	ctx.proj_res[1] = r_v->p_res[1];
	ctx.img_xy[0] = r_v->center_x - (ctx.proj_res[0] / 2);
	ctx.img_xy[1] = (data->x_data.curr_framebuf->res_y / 2)
		- (ctx.proj_res[1] / 2);
	ctx.tx = &r_v->sprite->animation->frames[r_v->sprite->curr_frame];
	ctx.tx_size_line = ctx.tx->size_line;
	ctx.fr_size_line = data->x_data.curr_framebuf->size_line;
	ctx.step_xy[0] = ctx.tx->res_x / (float)ctx.proj_res[0];
	ctx.step_xy[1] = ctx.tx->res_y / (float)ctx.proj_res[1];
	ctx.tx_xy[0] = 0;
	ctx.tx_xy[1] = 0;
	cull_non_visible(&ctx);
	ctx.fr_buff = (data->x_data.curr_framebuf->addr)
		+ ctx.img_xy[0] * data->x_data.curr_framebuf->bytes_pp
		+ (data->x_data.curr_framebuf->size_line) * ctx.img_xy[1];
	ctx.tx_buff = (ctx.tx->addr) + (int)ctx.tx_xy[0] * ctx.tx->bytes_pp
		+ (ctx.tx->size_line) * (int)ctx.tx_xy[1];
	ctx.tx_y = ctx.tx_xy[1];
	ctx.proj_res_y = ctx.proj_res[1];
	ctx.sp_z = r_v->pos_tr.y;
	put_sprite_on_img_pt2(&ctx);
}

// alpha color 0x980088ff
void	draw_sprites(t_data *data)
{
	size_t	zsorted_size;
	size_t	i;

	zsorted_size = transform_sprites_pos(data->sprites_zsorted, data->sprites,
			&(data->player), data->x_data.res);
	sort_sprites(data->sprites_zsorted, zsorted_size);
	i = 0;
	while (i < zsorted_size)
	{
		put_sprite_on_img(data, (&data->sprites_zsorted[i]));
		i++;
	}
}
