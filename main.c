#include "cub3d.h"
/*{'1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '1', '0', '1'},
{'1', '0', '1', '0', '0', '1'},
{'1', '1', '0', '0', 'N', '1'},
{'1', '1', '1', '1', '1', '1'}*/

int	main(void)
{
	static char		*map[7] = {
		"111111",
		"10s001",
		"11D101",
		"10Nso1",
		"110001",
		"111111",
		NULL
	};
	static t_verif	verif = {
		.no = "wall_textures/N_wall.xpm",
		.so = "wall_textures/S_wall.xpm",
		.we = "wall_textures/W_wall.xpm",
		.ea = "wall_textures/E_wall.xpm",
		.f = NULL,
		.c = NULL,
		.f_arr = {
		(0xb3c7bd >> (8 * 2)) & 0x0000ff,
		(0xb3c7bd >> 8) & 0x0000ff,
		0xb3c7bd & 0x0000ff
	},
		.c_arr = {
		(0x1980a6 >> (8 * 2)) & 0x0000ff,
		(0x1980a6 >> 8) & 0x0000ff,
		0x1980a6 & 0x0000ff
	},
		.map = map,
		.rows = 6,
		.cols = 6,
		.orient_set = 0
	};
	static t_data	data;

	if (!init(&data, &verif) || !read_resources(&data, &verif))
		return (free_data(&data), print_error(), 1);
	hook_up(&data);
}
