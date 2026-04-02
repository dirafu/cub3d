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
	transformed.x = s_rel_pos.x * player->cam_plane_normalized.x + s_rel_pos.y * (-player->dir.x);
	transformed.y = s_rel_pos.x * (-player->cam_plane_normalized.y) + s_rel_pos.y * player->dir.y;
	return (transformed);
}

size_t	transform_sprites_pos(t_sprite_rendering_view *r_view, t_sprite *sprites, t_player *player)
{
	size_t		i;
	size_t		visible;
	t_point2d	pos_transformed;
	float		projected_x;

	i = 0;
	visible = 0;
	while (sprites[i].animation)
	{
		pos_transformed = transform_pos(player, &(sprites[i]));
		if (pos_transformed.y > 0.01f)
		{
			projected_x = pos_transformed.x / pos_transformed.y;
			if (projected_x > -player->fov_scale
				&& projected_x < player->fov_scale && ++visible)
			{
				r_view[visible - 1].pos_transformed = pos_transformed;
				r_view[visible - 1].projected_x = projected_x;
				r_view[visible - 1].sprite = &(sprites[i]);
			}
		}
		i++;
	}
	r_view[visible].sprite = NULL;
	return (visible);
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
			if (j && zsorted[j - 1].pos_transformed.y < zsorted[j].pos_transformed.y)
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

void	put_sprite_on_img_pt3(float tx_xy[2], int img_xy[2], t_data *data, t_sprite_rendering_view *r_v)
{
	int	color;

	if ((img_xy[0] < 0 || img_xy[0] > data->x_data.res[0])
		|| (img_xy[1] < 0 || img_xy[1] > data->x_data.res[1]))
		return ;
	color = get_img_px_color(&(r_v->sprite->animation->frames[r_v->sprite->curr_frame]), tx_xy[0], tx_xy[1]);
	if (color != 0x980088 && img_xy[0] < data->x_data.res[0]
		&& r_v->pos_transformed.y < data->x_data.zbuff[img_xy[0]])
		put_px_on_img(&(data->x_data), img_xy[0], img_xy[1], color);
}

void	put_sprite_on_img_pt2(int proj_res[2], int img_xy[2], t_data *data, t_sprite_rendering_view *r_v)
{
	float	step_xy[2];
	float	tx_xy[2];
	int		img_y;
	int		proj_height;
	

	step_xy[0] = r_v->sprite->animation->frames[r_v->sprite->curr_frame].res_x / (float)proj_res[0];
	step_xy[1] = r_v->sprite->animation->frames[r_v->sprite->curr_frame].res_y / (float)proj_res[1];
	tx_xy[0] = 0;
	proj_height = proj_res[1];
	img_y = img_xy[1];
	while ((proj_res[0])--)
	{
		tx_xy[1] = 0;
		proj_res[1] = proj_height;
		img_xy[1] = img_y;
		while ((proj_res[1])--)
		{
			put_sprite_on_img_pt3(tx_xy, img_xy, data, r_v);
			tx_xy[1] += step_xy[1];
			img_xy[1]++;
		}
		tx_xy[0] += step_xy[0];
		img_xy[0]++;
	}
}

//proj_res[0] is width
//proj_res[1] is height
//img_xy[0] is x
//img_xy[1] is y
void	put_sprite_on_img(t_data *data, t_sprite_rendering_view *r_v)
{
	int		proj_res[2];
	int		img_xy[2];

	proj_res[0] = data->x_data.curr_framebuf->res_x / r_v->pos_transformed.y;
	proj_res[1] = data->x_data.curr_framebuf->res_y / r_v->pos_transformed.y;
	img_xy[0] = (((r_v->projected_x + data->player.fov_scale) / (data->player.fov_scale * 2))
				* data->x_data.curr_framebuf->res_x) - (proj_res[0] / 2);
	img_xy[1] = (data->x_data.curr_framebuf->res_y / 2) - (proj_res[1] / 2);
	put_sprite_on_img_pt2(proj_res, img_xy, data, r_v);
}

// alpha color 0x980088ff
void	draw_sprites(t_data *data)
{
	size_t	zsorted_size;
	size_t	i;

	zsorted_size = transform_sprites_pos(data->sprites_zsorted, data->sprites, &(data->player));
	sort_sprites(data->sprites_zsorted, zsorted_size);
	i = 0;
	while (i < zsorted_size)
	{
		put_sprite_on_img(data, (&data->sprites_zsorted[i]));
		i++;
	}
}
