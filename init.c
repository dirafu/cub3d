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
		if (!ft_create_new_image(&data->img_data[i],
				data->xconn, data->res[0], data->res[1]))
			return (false);
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

bool	init(t_data *data, t_verif *verif)
{
	data->map = map_struct_prep(verif->map);
	if (!data->map)
		return (false);
	data->player.fov_scale = tanf(FOV / 2.0
			* (M_PI / 180.0f) * ((float)RES_X / RES_Y));
	if (!x_init(&(data->x_data)) || !init_mouse(data))
		return (false);
	data->sprites_zsorted = alloc_zsorted(data);
	if (!data->sprites_zsorted)
		return (false);
	data->active_doors = alloc_active_doors(data);
	if (!data->active_doors)
		return (false);
	data->active_doors_count = 0;
	set_default_keybindings(data->input.keybindings);
	set_player(verif->map, &data->player);
	data->ceiling_color = (verif->c_arr[0] << (8 * 2))
		+ (verif->c_arr[1] << 8)
		+ (verif->c_arr[2]);
	data->floor_color = (verif->f_arr[0] << (8 * 2))
		+ (verif->f_arr[1] << 8)
		+ (verif->f_arr[2]);
	return (true);
}

void	hook_up(t_data *data)
{
	mlx_hook(data->x_data.win, 2, 1L << 0, key_down, &data->input);
	mlx_hook(data->x_data.win, 3, 1L << 1, key_up, &data->input);
	mlx_hook(data->x_data.win, 17, 0, exit_handler, data);
	mlx_hook(data->x_data.win, 6, 1L << 6, handle_mouse, data);
	data->time_data.last_frame_time = ft_get_time_us();
	mlx_loop_hook(data->x_data.xconn, game_loop, data);
	mlx_loop(data->x_data.xconn);
}
