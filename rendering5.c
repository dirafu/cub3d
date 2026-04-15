#include "cub3d.h"

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
