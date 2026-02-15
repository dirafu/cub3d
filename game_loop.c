#include "cub3d.h"

int	game_loop(t_data *data)
{
	uint64_t	utime_now;

	utime_now = ft_get_time_us();
    if (utime_now - data->time_data.last_frame_time < 16666)
	{
        return (0);
	}
	data->time_data.time_d = (utime_now - data->time_data.last_frame_time)
		/ 1000000.0;
	data->time_data.last_frame_time = utime_now;
	handle_keys(data);
	draw_frame(data);
	return (1);
}