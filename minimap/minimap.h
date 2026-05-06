/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:09:24 by ikiriush          #+#    #+#             */
/*   Updated: 2026/05/06 04:10:04 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# define MM_SCALE 0.25f
# define TILE_X 11
# define TILE_Y 7
# define SPAN_X 5
# define SPAN_Y 3
# define PI 3.14159

# include "../verif/verif.h"
# include <sys/param.h>

typedef struct s_minimap	t_minimap;

void	draw_bg(t_data *data);
void	draw_map(t_data *data);
void	cast_mm_cone(t_data *data);
void	draw_player(t_data *data);
void	draw_tile(t_data *data, int i, int j, int color);
void	draw_tiles(t_data *data);

#endif