#include "cub3d.h"

void	update_door_openness(t_map **a_d, size_t i, size_t *active_doors_count, t_time_data *time_data)
{
	if (a_d[i]->door_status == DOOR_STATUS_CLOSING)
	{
		a_d[i]->door_open_factor = ft_lerp(a_d[i]->door_open_factor, 0.0f, 4.0f * time_data->time_d);
		if ((a_d[i]->door_open_factor - 0.01) < 0.0)
		{
			a_d[i]->door_open_factor = 0.0f;
			a_d[i]->door_status = DOOR_STATUS_CLOSED;
			a_d[i] = a_d[--(*active_doors_count)];
		}
	}
	else if (a_d[i]->door_status == DOOR_STATUS_OPENING)
	{
		a_d[i]->door_open_factor = ft_lerp(a_d[i]->door_open_factor, 1.0f, 4.0f * time_data->time_d);
		if ((a_d[i]->door_open_factor + 0.01) > 1.0)
		{
			a_d[i]->door_open_factor = 1.0f;
			a_d[i]->door_status = DOOR_STATUS_OPENED;
			a_d[i]->door_open_time = time_data->last_frame_time;
			a_d[i] = a_d[--(*active_doors_count)];
		}
	}
}

void	update_doors_state(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->active_doors_count)
	{
		if (data->active_doors[i]->door_status == DOOR_STATUS_OPENED
			&& (data->time_data.last_frame_time - data->active_doors[i]->door_open_time)
			> DOOR_AUTO_CLOSE_T)
			data->active_doors[i]->door_status = DOOR_STATUS_CLOSING;
		update_door_openness(data->active_doors, i, &data->active_doors_count, &data->time_data);
		i++;
	}
}

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
	update_doors_state(data);
	handle_keys(data);
	draw_frame(data);
	return (1);
}