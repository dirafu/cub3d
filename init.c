#include "cub3d.h"

bool	x_init(t_x_data *data)
{
	int	i;

	i = 0;
	data->res[0] = RES_X;
	data->res[1] = RES_Y;
	data->xconn = mlx_init();
	if (!data->xconn)
		return (false);
	data->win = mlx_new_window(data->xconn, RES_X, RES_Y, "test");
	if (!data->win)
		return (false);
	while (i < 2)
	{
		data->img_data[i].img = mlx_new_image(data->xconn, RES_X, RES_Y);
		if (!data->img_data[i].img)
			return (false);
		data->img_data[i].addr = mlx_get_data_addr(data->img_data[i].img,
				&(data->img_data[i].bpp),
				&(data->img_data[i].size_line), &(data->img_data[i].endian));
		data->img_data[i].res_x = data->res[0];
		data->img_data[i].res_y = data->res[1];
		i++;
	}
	data->curr_framebuf = &(data->img_data[(data->framebuf_sel)++ % 2]);
	return (true);
}

t_sprite_rendering_view	*alloc_zsorted(t_data *data)
{
	size_t					sprite_c;
	t_sprite_rendering_view	*s_view;

	sprite_c = count_map_cells(data->map, CELL_SPRITE);
	s_view = ft_calloc(sprite_c + 1, sizeof(*s_view));
	if (!s_view)
		return (NULL);
	return (s_view);
}

t_map	**alloc_active_doors(t_data *data)
{
	size_t	door_c;
	t_map	**active_doors;

	door_c = count_map_cells(data->map, CELL_DOOR);
	active_doors = ft_calloc(door_c + 1, sizeof(*active_doors));
	if (!active_doors)
		return (NULL);
	return (active_doors);
}

bool	init(t_data *data)
{
	if (!x_init(&(data->x_data)))
		return (false);
	data->sprites_zsorted = alloc_zsorted(data);
	if (!data->sprites_zsorted)
		return (false);
	data->active_doors = alloc_active_doors(data);
	if (!data->active_doors)
		return (false);
	data->active_doors_count = 0;
	return (true);
}