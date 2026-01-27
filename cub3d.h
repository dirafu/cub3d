#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# define RES_X 640
# define RES_Y 480
# define FOV 75
# define MAX_SIMULTANEOUS_KEYS 10

typedef enum actions
{
	ACT_LEFT,
	ACT_RIGHT,
	ACT_FORWARD,
	ACT_BACKWARD,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_COUNT
}	t_actions;

// typedef float	t_point2d[2];

typedef	struct s_point2d
{
	float	x;
	float	y;
}	t_point2d;

typedef struct s_x_data
{
	void		*xconn;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			res[2];
}	t_x_data;

typedef	struct s_player
{
	t_point2d	dir;
	t_point2d	pos;
	t_point2d	cam_plane;
}	t_player;

typedef	struct s_keybindings
{
	t_actions	action;
	int			keysym;
}	t_keybindings;

typedef	struct s_input
{
	bool			actions[ACT_COUNT];
	t_keybindings	keybindings[ACT_COUNT];
}	t_input;

typedef	struct s_data
{
	t_x_data	x_data;
	t_player	player;
	t_input		input;
}	t_data;

//input
void	set_default_keybindings(t_keybindings *keybindings);
int		key_down(int keysym, t_input *input);
int		key_up(int keysym, t_input *input);
void	put_px_on_img(t_x_data *x_data, int x, int y, int color);
int		game_loop(t_data *data);

//vector op-s
t_point2d	vec2d_sum(t_point2d p1, t_point2d p2);

#endif
