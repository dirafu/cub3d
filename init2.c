#include "cub3d.h"

bool	ft_create_new_image(t_img_data *img_d, void *xconn, int x, int y)
{
	img_d->img = mlx_new_image(xconn, x, y);
	if (!img_d->img)
		return (false);
	img_d->addr = mlx_get_data_addr(img_d->img,
			&(img_d->bpp),
			&(img_d->size_line), &(img_d->endian));
	img_d->bytes_pp = img_d->bpp / 8;
	img_d->res_x = x;
	img_d->res_y = y;
	return (true);
}

bool	init_mouse(t_data *data)
{
	mlx_mouse_hide(data->x_data.xconn, data->x_data.win);
	mlx_mouse_move(data->x_data.xconn, data->x_data.win,
		data->x_data.res[0] / 2, data->x_data.res[1] / 2);
	return (true);
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
	player->cam_plane_normalized = player->cam_plane;
	player->cam_plane = vec2d_mul(player->cam_plane, player->fov_scale);
	player->radius = PLAYER_RADIUS;
	player->angle_rad = atan2f(player->dir.y, player->dir.x);
	if (player->angle_rad < 0)
		player->angle_rad += M_PI * 2;
}
