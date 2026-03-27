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

t_sprite_animation	*get_animation(t_animated_sprites_info *info, t_sprite_animation* animations, char sprite_id)
{
	size_t	i;

	i = 0;
	while (info[i].dir)
	{
		if (info[i].sprite_id == sprite_id)
		{
			return (&(animations[i]));
		}
		i++;
	}
	return (NULL);
}

//IT IS A DEAD FUNCTION THAT SHOULD BE DELETED
// void	assign_sprites_to_map(t_animated_sprites_info *info, t_data *data)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	k;

// 	i = 0;
// 	while (info[i].dir)
// 	{
// 		j = 0;
// 		while (data->map[j])
// 		{
// 			k = 0;
// 			while (data->map[j][k].type != CELL_TERMINATOR)
// 			{
// 				if (data->map[j][k].type == CELL_SPRITE
// 					&& data->map[j][k].sprite_id == info[i].sprite_id)
// 					data->map[j][k].sprite = &(data->sprites_animations[i]);
// 				k++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

size_t	count_sprites_on_map(t_map **map)
{
	size_t	i;
	size_t	j;
	size_t	c;

	i = 0;
	c = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j].type != CELL_TERMINATOR)
		{
			if (map[i][j].type == CELL_SPRITE)
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

// fill sprites array with pos, respective *animation
void	link_sprites_to_map(t_data *data, t_sprite *sprites, t_animated_sprites_info *info)
{
	size_t	i;
	size_t	j;
	size_t	sprite_n;

	i = 0;
	sprite_n = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j].type != CELL_TERMINATOR)
		{
			if (data->map[i][j].type == CELL_SPRITE)
			{
				sprites[sprite_n].pos.y = -(i + 0.5f);
				sprites[sprite_n].pos.x = (j + 0.5f);
				data->map[i][j].sprite = &(sprites[sprite_n]);
				data->map[i][j].sprite->animation = get_animation(info, data->sprites_animations, data->map[i][j].sprite_id);
				sprite_n++;
			}
			j++;
		}
		i++;
	}
}

t_sprite	*init_sprites_array(t_data *data, t_animated_sprites_info *info)
{
	size_t		sprite_c;
	t_sprite	*sprites;

	sprite_c = count_sprites_on_map(data->map);
	sprites = ft_calloc(sprite_c + 1, sizeof(*(data->sprites)));
	if (!sprites)
		return(NULL);
	link_sprites_to_map(data, sprites, info);
	return (sprites);
}

t_sprite_rendering_view	*alloc_zsorted(t_data *data)
{
	// size_t					i;
	size_t					sprite_c;
	t_sprite_rendering_view	*s_view;

	sprite_c = count_sprites_on_map(data->map);
	s_view = ft_calloc(sprite_c + 1, sizeof(*s_view));
	if (!s_view)
		return (NULL);
	return (s_view);
}

bool	read_sprites(t_data *data)
{
	//just as an example, probably it will be list instead of array
	static t_animated_sprites_info	sprites_info[3] = {
		{39, "sprites/doge", 'o'},
		{49, "sprites/soldier", 's'},
		{-1, NULL, '\0'}
	};
	static size_t	number_of_sprites = 2;
	size_t			i = 0;

	data->sprites_animations = ft_calloc(number_of_sprites + 1, sizeof(*(data->sprites)));
	if (!data->sprites_animations)
		return (false);
		//todo: handle properly
	while (i < number_of_sprites)
	{
		data->sprites_animations[i].frame_duration = A_FRAME_DUR_U;
		data->sprites_animations[i].num_of_frames = sprites_info[i].num_of_frames;
		data->sprites_animations[i].frames = ft_calloc(sprites_info[i].num_of_frames, sizeof(*(data->sprites_animations->frames)));
		if (!data->sprites_animations[i].frames)
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
			data->sprites_animations[i].frames[j].img = mlx_xpm_file_to_image(data->x_data.xconn, filename,
				&(data->sprites_animations[i].frames[j].res_x), &(data->sprites_animations[i].frames[j].res_y));
			free(filename);
			if (!data->sprites_animations[i].frames[j].img)
				return (false);
				//todo: handle properly
			data->sprites_animations[i].frames[j].addr = mlx_get_data_addr(data->sprites_animations[i].frames[j].img,
				&(data->sprites_animations[i].frames[j].bpp), &(data->sprites_animations[i].frames[j].size_line),
				&(data->sprites_animations[i].frames[j].endian));
			j++;
		}
		i++;
	}
	data->sprites = init_sprites_array(data, sprites_info);
	if (!data->sprites)
		return (false);
		//todo: handle properly
	data->sprites_zsorted = alloc_zsorted(data);
	if (!data->sprites_zsorted)
		return (false);
		//todo: handle properly
	return (true);
}

bool	read_resources(t_data *data)
{
	if (!read_wall_textures(data) || !read_sprites(data))
		return (false);
	return (true);
}