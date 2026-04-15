#include "cub3d.h"

bool	read_wall_textures(t_data *data, char **texture_filenames)
{
	size_t		i;

	i = 0;
	while (i < WALL_TEX_COUNT)
	{
		data->wall_textures[i].img = mlx_xpm_file_to_image(
				data->x_data.xconn, texture_filenames[i],
				&(data->wall_textures[i].res_x),
				&(data->wall_textures[i].res_y));
		if (!data->wall_textures[i].img)
			return (false);
		data->wall_textures[i].addr = mlx_get_data_addr(
				data->wall_textures[i].img, &data->wall_textures[i].bpp,
				&data->wall_textures[i].size_line,
				&data->wall_textures[i].endian);
		data->wall_textures[i].bytes_pp = data->wall_textures[i].bpp / 8;
		i++;
	}
	return (true);
}
