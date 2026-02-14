#include "cub3d.h"

void	free_textures(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		if (data->textures[i].img && data->x_data.xconn)
			mlx_destroy_image(data->x_data.xconn, data->textures[i].img);
		data->textures[i].img = NULL;
	}
}

void	free_data(t_data *data)
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

void	print_error(void)
{
	perror("Cub3d: an error occured:");
}

int	exit_handler(t_data *data)
{
	free_data(data);
	exit(1);
}
