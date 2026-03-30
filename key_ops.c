#include "cub3d.h"

void	set_default_keybindings(t_keybindings *keybindings)
{
	keybindings[0].action = ACT_LEFT;
	keybindings[0].keysym = 65361;
	keybindings[1].action = ACT_RIGHT;
	keybindings[1].keysym = 65363;
	keybindings[2].action = ACT_FORWARD;
	keybindings[2].keysym = 119;
	keybindings[3].action = ACT_BACKWARD;
	keybindings[3].keysym = 115;
	keybindings[4].action = ACT_STRAFE_LEFT;
	keybindings[4].keysym = 97;
	keybindings[5].action = ACT_STRAFE_RIGHT;
	keybindings[5].keysym = 100;
	keybindings[6].action = ACT_OPEN_DOOR;
	keybindings[6].keysym = 32;
}

int	key_down(int keysym, t_input *input)
{
	int	i;

	i = 0;
	while (i < ACT_COUNT)
	{
		if (input->keybindings[i].keysym == keysym)
			input->actions[input->keybindings[i].action] = true;
		i++;
	}
	return (1);
}

int	key_up(int keysym, t_input *input)
{
	int	i;

	i = 0;
	while (i < ACT_COUNT * 2)
	{
		if (input->keybindings[i].keysym == keysym)
			input->actions[input->keybindings[i].action] = false;
		i++;
	}
	return (1);
}

void	handle_doors_interactions(t_data *data)
{
	t_point2d	door_pos;
	t_map		*door_cell;

	if (data->input.actions[ACT_OPEN_DOOR])
	{
		door_pos = vec2d_sum(data->player.pos, data->player.dir);
		door_cell = &(data->map[-((int)door_pos.y)][(int)door_pos.x]);
		if (door_cell->type == CELL_DOOR
			&& &data->map[-(int)data->player.pos.y][(int)data->player.pos.x]
			!= door_cell)
		{
			if (door_cell->door_status == DOOR_STATUS_CLOSED)
			{
				door_cell->door_status = DOOR_STATUS_OPENING;
				data->active_doors[data->active_doors_count++] = door_cell;
			}
			if (door_cell->door_status == DOOR_STATUS_OPENED)
				door_cell->door_status = DOOR_STATUS_CLOSING;
		}
	}
}

void	handle_keys(t_data *data)
{
	double	d_t;

	d_t = data->time_data.time_d;
	if (data->input.actions[ACT_LEFT])
		rotate_player(&data->player, 90.0f * d_t);
	else if (data->input.actions[ACT_RIGHT])
		rotate_player(&data->player, -90.0f * d_t);
	if (data->input.actions[ACT_FORWARD])
		step_player(&data->player, data->map, 2.0f * d_t, PARALLEL);
	else if (data->input.actions[ACT_BACKWARD])
		step_player(&data->player, data->map, -2.0f * d_t, PARALLEL);
	if (data->input.actions[ACT_STRAFE_RIGHT])
		step_player(&data->player, data->map, 2.0f * d_t, PERPENDICULAR);
	else if (data->input.actions[ACT_STRAFE_LEFT])
		step_player(&data->player, data->map, -2.0f * d_t, PERPENDICULAR);
	handle_doors_interactions(data);
}
