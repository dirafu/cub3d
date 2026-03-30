#include "cub3d.h"

void	free_sprites_array(t_data *data)
{
	if (data)
	{
		free(data->sprites);
		data->sprites = NULL;
		free(data->sprites_zsorted);
		data->sprites_zsorted = NULL;
	}
}

void	free_textures(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < WALL_TEX_COUNT)
	{
		if (data->wall_textures[i].img && data->x_data.xconn)
			mlx_destroy_image(data->x_data.xconn, data->wall_textures[i].img);
		data->wall_textures[i].img = NULL;
		i++;
	}
	i = 0;
	while (i < DOOR_TEX_COUNT)
	{
		if (data->door_textures[i].img && data->x_data.xconn)
			mlx_destroy_image(data->x_data.xconn, data->door_textures[i].img);
		data->door_textures[i].img = NULL;
		i++;
	}
}

void	free_xdata(t_data *data)
{
	int	i;

	i = 0;
	if (data->x_data.win && data->x_data.xconn)
	{
		mlx_destroy_window(data->x_data.xconn, data->x_data.win);
		data->x_data.win = NULL;
	}
	while (i < 2)
	{
		if (data->x_data.img_data[i].img && data->x_data.xconn)
		{
			mlx_destroy_image(data->x_data.xconn, data->x_data.img_data[i].img);
			data->x_data.img_data[i].img = NULL;
		}
		i++;
	}
	free_textures(data);
	if (data->x_data.xconn)
	{
		mlx_destroy_display(data->x_data.xconn);
		free(data->x_data.xconn);
		data->x_data.xconn = NULL;
	}
	data->x_data.curr_framebuf = NULL;
}
