#include "cub3d.h"

void	free_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (data && data->map && data->map[i])
	{
		free(data->map[i]);
		data->map[i] = NULL;
		i++;
	}
	if (data)
	{
		free(data->map);
		data->map = NULL;
		free(data->active_doors);
		data->active_doors = NULL;
	}
}

void	free_sprites(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (data && data->sprites_animations
		&& data->sprites_animations[i].frames)
	{
		j = 0;
		while (j < data->sprites_animations[i].num_of_frames)
		{
			if (data->x_data.xconn && data->sprites_animations[i].frames[j].img)
				mlx_destroy_image(data->x_data.xconn,
					data->sprites_animations[i].frames[j].img);
			data->sprites_animations[i].frames[j].img = NULL;
			j++;
		}
		free(data->sprites_animations[i].frames);
		data->sprites_animations[i].frames = NULL;
		i++;
	}
	free(data->sprites_animations);
	data->sprites_animations = NULL;
}

void	free_data(t_data *data)
{
	free_map(data);
	free_sprites(data);
	free_sprites_array(data);
	free_xdata(data);
	struct_destroyer(data->verif);
}

void	print_error(void)
{
	perror("Cub3d: an error occured");
}

int	exit_handler(t_data *data)
{
	free_data(data);
	exit(1);
}
