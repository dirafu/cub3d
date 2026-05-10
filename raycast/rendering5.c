/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:52:25 by vlchinen          #+#    #+#             */
/*   Updated: 2026/05/07 16:52:26 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	transform_sprites_pos(t_sprite_rendering_view *rview,
	t_sprite *sprites, t_player *p, int res[2])
{
	size_t		i;
	size_t		vis;

	i = 0;
	vis = 0;
	while (sprites[i].animation)
	{
		rview[vis].pos_tr = transform_pos(p, &(sprites[i]));
		if (rview[vis].pos_tr.y > 0.1f)
		{
			rview[vis].p_res[1] = res[1] / (rview[vis].pos_tr.y * p->hor_scale);
			rview[vis].p_res[0] = rview[vis].p_res[1]
				* ((float)sprites[i].animation->frames->res_x
					/ sprites[i].animation->frames->res_y);
			rview[vis].p_x = rview[vis].pos_tr.x / rview[vis].pos_tr.y;
			rview[vis].center_x = (((rview[vis].p_x + p->cam_scale)
						/ (p->cam_scale * 2)) * res[0]);
			if (rview[vis].center_x + rview[vis].p_res[0] / 2 > 0
				&& rview[vis].center_x - rview[vis].p_res[0] / 2 < res[0])
				rview[vis++].sprite = &(sprites[i]);
		}
		i++;
	}
	rview[vis].sprite = NULL;
	return (vis);
}
