#include "cub3d.h"

int	game_loop(t_data *data)
{
	handle_keys(data);
	draw_frame(data);
	// exit(1);
	return (1);
}
