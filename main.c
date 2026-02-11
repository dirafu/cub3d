#include "cub3d.h"
/*{'1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '1', '0', '1'},
{'1', '0', '1', '0', '0', '1'},
{'1', '1', '0', '0', 'N', '1'},
{'1', '1', '1', '1', '1', '1'}*/

void	*init(t_x_data *data)
{
	int	i;

	i = 0;
	data->res[0] = RES_X;
	data->res[1] = RES_Y;
	data->xconn = mlx_init();
	if (!data->xconn)
		return (NULL);
	data->win = mlx_new_window(data->xconn, RES_X, RES_Y, "test");
	if (!data->win)
		return (NULL);
	while (i < 2)
	{
		data->img_data[i].img = mlx_new_image(data->xconn, RES_X, RES_Y);
		if (!data->img_data[i].img)
			return (NULL);
		data->img_data[i].addr = mlx_get_data_addr(data->img_data[i].img,
				&(data->img_data[i].bpp),
				&(data->img_data[i].size_line), &(data->img_data[i].endian));
		i++;
	}
	data->curr_framebuf = &(data->img_data[(data->framebuf_sel)++ % 2]);
	return (data);
}

bool	set_player_pt2(char c, t_player *player)
{
	if (c == 'N')
	{
		player->dir.x = 0;
		player->dir.y = 1;
	}
	else if (c == 'W')
	{
		player->dir.x = -1;
		player->dir.y = 0;
	}
	else if (c == 'S')
	{
		player->dir.x = 0;
		player->dir.y = -1;
	}
	else if (c == 'E')
	{
		player->dir.x = 1;
		player->dir.y = 0;
	}
	else
		return (false);
	return (true);
}

void	set_position(char **map, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (set_player_pt2(map[i][j], player))
			{
				player->pos.y = -((float)i + 0.5);
				player->pos.x = (float)j + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	set_player(char **map, t_player *player)
{
	set_position(map, player);
	player->cam_plane.x = player->dir.y;
	player->cam_plane.y = -player->dir.x;
	player->cam_plane = vec2d_mul(player->cam_plane, player->fov_scale);
}

int	main(void)
{
	char	*map[7] = {
			"111111",
			"100001",
			"110101",
			"100001",
			"11N001",
			"111111",
			NULL
			};
	static t_data	data;

	data.map = map;
	data.player.fov_scale = tanf(FOV / 2.0 * (M_PI / 180.0f));
	if (!init(&data.x_data))
		return (free_data(&data), print_error(), 1);
	set_default_keybindings(data.input.keybindings);
	set_player(map, &data.player);
	mlx_hook(data.x_data.win, 2, 1L << 0, key_down, &data.input);
	mlx_hook(data.x_data.win, 3, 1L << 1, key_up, &data.input);
	mlx_hook(data.x_data.win, 17, 0, exit_handler, &data);
	data.time_data.last_frame_time = ft_get_time_us();
	mlx_loop_hook(data.x_data.xconn, game_loop, &data);
	mlx_loop(data.x_data.xconn);
}
