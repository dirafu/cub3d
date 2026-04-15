#include "cub3d.h"

t_sprite_animation	*get_animation(t_animated_sprites_info *info,
	t_sprite_animation *animations, char sprite_id)
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

size_t	count_map_cells(t_map **map, t_map_cell_type type)
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
			if (map[i][j].type == type)
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

// fill sprites array with pos, respective *animation
void	link_sprites_to_map(t_data *data, t_sprite *sprites,
	t_animated_sprites_info *info)
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
				data->map[i][j].sprite->animation = get_animation(info,
						data->sprites_animations, data->map[i][j].sprite_id);
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

	sprite_c = count_map_cells(data->map, CELL_SPRITE);
	sprites = ft_calloc(sprite_c + 1, sizeof(*(data->sprites)));
	if (!sprites)
		return (NULL);
	link_sprites_to_map(data, sprites, info);
	return (sprites);
}

bool	read_resources(t_data *data, t_verif *verif)
{
	char	*texture_filenames[WALL_TEX_COUNT];

	texture_filenames[0] = verif->no;
	texture_filenames[1] = verif->we;
	texture_filenames[2] = verif->so;
	texture_filenames[3] = verif->ea;
	if (!read_wall_textures(data, texture_filenames)
		|| !read_door_textures(data)
		|| !read_sprites(data))
		return (false);
	return (true);
}
