#include "cub3d.h"
/*{'1', '1', '1', '1', '1', '1'},
{'1', '0', '0', '1', '0', '1'},
{'1', '0', '1', '0', '0', '1'},
{'1', '1', '0', '0', 'N', '1'},
{'1', '1', '1', '1', '1', '1'}*/
void	*init(t_x_data *data)
{
	data->xconn = mlx_init();
	if (!data->xconn)
		return (NULL);
	data->win = mlx_new_window(data->xconn, RES_X, RES_Y, "test");
	if (!data->win)
		return (free(data->xconn), NULL);
	data->img = mlx_new_image(data->xconn, RES_X, RES_Y);
	if (!data->img)
		return ((void)mlx_destroy_window(data->xconn, data->win),
			free(data->xconn), NULL);
			// maybe add x_data_free() to clear all non-NULL ptrs in struct is significantly better for readability?
	data->addr = mlx_get_data_addr(data->img, &(data->bpp),
			&(data->size_line), &(data->endian));
	return (data);
}

int	main(void)
{
	char	*map[5] = {
			"111111",
			"100101",
			"101001",
			"1100N1",
			"111111"
			};
	static t_x_data	x_data;

	//parse map -> validate map (is it closed) -
}