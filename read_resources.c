#include "cub3d.h"

bool	read_wall_textures(t_data *data)
{
	size_t		i;
	static char	*texture_filenames[] = {
		"wall_textures/N_wall.xpm",
		"wall_textures/W_wall.xpm",
		"wall_textures/S_wall.xpm",
		"wall_textures/E_wall.xpm"
	};

	i = 0;
	while (i < TEXTURE_COUNT)
	{
		data->wall_textures[i].img = mlx_xpm_file_to_image(data->x_data.xconn, texture_filenames[i], &(data->wall_textures[i].res_x), &(data->wall_textures[i].res_y));
		if (!data->wall_textures[i].img)
			return (false);
		data->wall_textures[i].addr = mlx_get_data_addr(data->wall_textures[i].img, &data->wall_textures[i].bpp, &data->wall_textures[i].size_line, &data->wall_textures[i].endian);
		i++;
	}
	return (true);
}

char	*get_full_frame_filename(char *dir, size_t num_width, size_t frame_num)
{
	char	*filename;
	char	*temp;
	char	*full_filename;

	temp = ft_itoa_with_leading_zeroes(frame_num, num_width);
	if (!temp)
		return (NULL);
	filename = ft_strjoin(temp, ".xpm");
	free(temp);
	if (!filename)
		return (NULL);
	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (free(filename), NULL);
	full_filename = ft_strjoin(temp, filename);
	free(temp);
	free(filename);
	if (!full_filename)
		return (NULL);
	return(full_filename);	
}

bool	read_sprites(t_data *data)
{
	//just as an example, probably it will be list instead of array
	static t_animated_sprites_info	sprites_info[3] = {
		{39, "doge"},
		{49, "soldier"},
		{-1, NULL}
	};
	static size_t	number_of_sprites = 2;
	size_t			i = 0;

	data->sprites_textures = ft_calloc(number_of_sprites, sizeof(*(data->sprites_textures)));
	if (!data->sprites_textures)
		return (false);
		//todo: handle properly
	while (i < number_of_sprites)
	{
		data->sprites_textures[i] = ft_calloc(sprites_info[i].num_of_frames + 1, sizeof(**(data->sprites_textures)));
		if (!(data->sprites_textures)[i])
			return (false);
			//todo: handle properly
		i++;
	}
	
	i = 0;
	size_t			j;
	char			*filename;
	size_t			filename_width;
	while (i < number_of_sprites)
	{
		j = 0;
		filename_width = ft_num_str_width(sprites_info[i].num_of_frames - 1);
		while (j < sprites_info[i].num_of_frames)
		{
			filename = get_full_frame_filename(sprites_info[i].dir, filename_width, j);
			if (!filename)
				return (false);
				//todo: handle properly
			data->sprites_textures[i][j].img = mlx_xpm_file_to_image(data->x_data.xconn, filename,
				&(data->sprites_textures[i][j].res_x), &(data->sprites_textures[i][j].res_y));
			free(filename);
			if (!data->sprites_textures[i][j].img)
				return (false);
				//todo: handle properly
			data->sprites_textures[i][j].addr = mlx_get_data_addr(data->sprites_textures[i][j].img,
				&(data->sprites_textures[i][j].bpp), &(data->sprites_textures[i][j].size_line),
				&(data->sprites_textures[i][j].endian));
			j++;
		}
		i++;
	}
	return (true);
}

bool	read_resources(t_data *data)
{
	if (!read_wall_textures(data) || !read_sprites(data))
		return (false);
	return (true);
}