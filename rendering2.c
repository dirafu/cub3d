#include "cub3d.h"

void	fill_render_info(t_render_facilities *rf,
		t_player *player, t_point2d *raydir)
{
	rf->hit = HIT_NONE;
	rf->x = player->pos.x;
	rf->y = player->pos.y;
	rf->t_x = 1 / (raydir->x * (((raydir->x < 0) * -2) + 1));
	rf->t_y = 1 / (raydir->y * (((raydir->y < 0) * -2) + 1));
	if (raydir->x < 0)
		rf->next_x = (player->pos.x - floorf(player->pos.x)) * rf->t_x;
	else
		rf->next_x = (floorf(player->pos.x) + 1 - player->pos.x) * rf->t_x;
	if (raydir->y < 0)
		rf->next_y = (player->pos.y - floorf(player->pos.y)) * rf->t_y;
	else
		rf->next_y = (floorf(player->pos.y) + 1 - player->pos.y) * rf->t_y;
	rf->step_x = ((raydir->x < 0) * -2) + 1;
	rf->step_y = ((raydir->y < 0) * -2) + 1;
	rf->overall_number_of_steps = 0;
	rf->tex_x = 0;
	rf->passed_door = NULL;
	rf->door_plate = false;
}

t_point2d	transform_pos(t_player *player, t_sprite *sprite)
{
	t_point2d	s_rel_pos;
	t_point2d	transformed;

	s_rel_pos = vec2d_sub(sprite->pos, player->pos);
	transformed.x = s_rel_pos.x * player->cam_plane_normalized.x
		+ s_rel_pos.y * (-player->dir.x);
	transformed.y = s_rel_pos.x * (-player->cam_plane_normalized.y)
		+ s_rel_pos.y * player->dir.y;
	return (transformed);
}

size_t	transform_sprites_pos(t_sprite_rendering_view *r_view,
	t_sprite *sprites, t_player *player, int res[2])
{
	size_t		i;
	size_t		vis;

	i = 0;
	vis = 0;
	while (sprites[i].animation)
	{
		r_view[vis].pos_tr = transform_pos(player, &(sprites[i]));
		if (r_view[vis].pos_tr.y > 0.1f)
		{
			r_view[vis].p_res[1] = res[1] / r_view[vis].pos_tr.y;
			r_view[vis].p_res[0] = r_view[vis].p_res[1]
				* ((float)sprites[i].animation->frames->res_x
					/ sprites[i].animation->frames->res_y);
			r_view[vis].p_x = r_view[vis].pos_tr.x / r_view[vis].pos_tr.y;
			r_view[vis].center_x = (((r_view[vis].p_x + player->fov_scale)
						/ (player->fov_scale * 2)) * res[0]);
			if (r_view[vis].center_x + r_view[vis].p_res[0] / 2 > 0
				&& r_view[vis].center_x - r_view[vis].p_res[0] / 2 < res[0])
				r_view[vis++].sprite = &(sprites[i]);
		}
		i++;
	}
	r_view[vis].sprite = NULL;
	return (vis);
}

void	sort_sprites(t_sprite_rendering_view *zsorted, size_t zsorted_size)
{
	size_t					i;
	size_t					j;
	t_sprite_rendering_view	tmp;

	i = 0;
	while (zsorted[i].sprite)
	{
		j = 0;
		while (j < zsorted_size - i)
		{
			if (j && zsorted[j - 1].pos_tr.y
				< zsorted[j].pos_tr.y)
			{
				tmp = zsorted[j];
				zsorted[j] = zsorted[j - 1];
				zsorted[j - 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

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
