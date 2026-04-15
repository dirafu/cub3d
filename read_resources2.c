#include "cub3d.h"

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
	return (full_filename);
}

bool	read_sprites_pt3(t_img_data *img_data, void *xconn, char *filename)
{
	img_data->img = mlx_xpm_file_to_image(
			xconn, filename,
			&(img_data->res_x),
			&(img_data->res_y));
	free(filename);
	if (!img_data->img)
		return (false);
	img_data->addr = mlx_get_data_addr(img_data->img,
			&(img_data->bpp), &(img_data->size_line),
			&(img_data->endian));
	img_data->bytes_pp = img_data->bpp / 8;
	return (true);
}

bool	read_sprites_pt2(t_data *data,
	t_animated_sprites_info *s_info, size_t number_of_sprites)
{
	size_t	i;
	size_t	j;
	size_t	fn_width;
	char	*filename;

	i = 0;
	while (i < number_of_sprites)
	{
		j = 0;
		fn_width = ft_num_str_width(s_info[i].num_of_frames - 1);
		while (j < s_info[i].num_of_frames && ++j)
		{
			filename = get_full_frame_filename(s_info[i].dir, fn_width, j - 1);
			if (!filename)
				return (false);
			if (!read_sprites_pt3(&data->sprites_animations[i].frames[j - 1],
					data->x_data.xconn, filename))
				return (false);
		}
		i++;
	}
	data->sprites = init_sprites_array(data, s_info);
	if (!data->sprites)
		return (false);
	return (true);
}

bool	read_sprites(t_data *data)
{
	static t_animated_sprites_info	sprites_info[3] = {
	{39, "sprites/doge", 'o'},
	{49, "sprites/soldier", 's'},
	{-1, NULL, '\0'}
	};
	static size_t					number_of_sprites = 2;
	size_t							i;

	i = 0;
	data->sprites_animations = ft_calloc(
			number_of_sprites + 1, sizeof(*(data->sprites)));
	if (!data->sprites_animations)
		return (false);
	while (i < number_of_sprites && ++i)
	{
		data->sprites_animations[i - 1].frame_duration = A_FRAME_DUR_U;
		data->sprites_animations[i - 1].num_of_frames
			= sprites_info[i - 1].num_of_frames;
		data->sprites_animations[i - 1].frames = ft_calloc(
				sprites_info[i - 1].num_of_frames,
				sizeof(*(data->sprites_animations->frames)));
		if (!data->sprites_animations[i - 1].frames)
			return (false);
	}
	return (read_sprites_pt2(data, sprites_info, number_of_sprites));
}

bool	read_door_textures(t_data *data)
{
	size_t		i;
	static char	*texture_filenames[] = {
		"door_textures/face.xpm",
		"door_textures/side.xpm",
	};

	i = 0;
	while (i < DOOR_TEX_COUNT)
	{
		data->door_textures[i].img = mlx_xpm_file_to_image(data->x_data.xconn,
				texture_filenames[i], &(data->door_textures[i].res_x),
				&(data->door_textures[i].res_y));
		if (!data->door_textures[i].img)
			return (false);
		data->door_textures[i].addr = mlx_get_data_addr(
				data->door_textures[i].img, &data->door_textures[i].bpp,
				&data->door_textures[i].size_line,
				&data->door_textures[i].endian);
		data->door_textures[i].bytes_pp = data->door_textures[i].bpp / 8;
		i++;
	}
	return (true);
}
