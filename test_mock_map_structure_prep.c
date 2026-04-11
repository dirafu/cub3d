#include "cub3d.h"

size_t	map_col_size(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

void	match_map_char(t_map *map_cell, char cell_literal)
{
	if (cell_literal == '1')
		map_cell->type = CELL_WALL;
	else if (cell_literal == '0' || ft_strchr("NWES", cell_literal))
		map_cell->type = CELL_EMPTY;
	else if (cell_literal == 'D')
		map_cell->type = CELL_DOOR;
	else if (cell_literal == ' ')
		map_cell->type = CELL_NONE;
	else
	{
		map_cell->type = CELL_SPRITE;
		map_cell->sprite_id = cell_literal;
	}
}

t_map	**test_mock_map_structure_prep(char **map)
{
	size_t	i;
	size_t	j;
	size_t	row_len;
	size_t	col_size;
	t_map	**map_struct;

	col_size = map_col_size(map);
	i = 0;
	map_struct = ft_calloc(col_size + 1, sizeof(*map_struct));
	if (!map_struct)
		return (NULL);
	while (map[i])
	{
		j = 0;
		row_len = ft_strlen(map[i]);
		map_struct[i] = ft_calloc(row_len + 1, sizeof(**map_struct));
		if (!map_struct[i])
			return (NULL);
		while (map[i][j])
		{
			match_map_char(&(map_struct[i][j]), map[i][j]);
			if (map_struct[i][j].type == CELL_DOOR)
			{
				if (map[i][j - 1] == '1' && map[i][j + 1] == '1')
					map_struct[i][j].door_orientation = HORIZONTAL;
				else
					map_struct[i][j].door_orientation = VERTICAL;
			}
			j++;
		}
		i++;
	}
	return (map_struct);
}
