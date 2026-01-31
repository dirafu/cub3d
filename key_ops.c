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
	while (i < ACT_COUNT)
	{
		if (input->keybindings[i].keysym == keysym)
			input->actions[input->keybindings[i].action] = false;
		i++;
	}
	return (1);
}
