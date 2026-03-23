#include "cub3d.h"

void	free_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		data->map[i] = NULL;
		i++;
	}
	free(data->map);
	data->map = NULL;
}

void	free_sprites(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data->sprites[i].frames)
	{
		j = 0;
		while (j < data->sprites[i].num_of_frames)
		{
			mlx_destroy_image(data->x_data.xconn, data->sprites[i].frames[j].img);
			data->sprites[i].frames[j].img = NULL;
			j++;
		}
		free(data->sprites[i].frames);
		data->sprites[i].frames = NULL;
		i++;
	}
	free(data->sprites);
	data->sprites = NULL;
}

void	free_data(t_data *data)
{
	free_map(data);
	free_sprites(data);
	free_xdata(data);
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
