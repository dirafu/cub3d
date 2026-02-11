#ifndef CUB3D_H
# define CUB3D_H

# define _DEFAULT_SOURCE
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# define RES_X 640
# define RES_Y 480
# define FOV 90
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

typedef enum hit_type
{
	HIT_NONE,
	VERTICAL,
	HORIZONTAL
}	t_hit_type;

enum	direction
{
	PARALLEL,
	PERPENDICULAR
};

// typedef float	t_point2d[2];

typedef	struct s_point2d
{
	float	x;
	float	y;
}	t_point2d;

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}	t_img_data;

typedef struct s_x_data
{
	t_img_data	img_data[2];
	t_img_data	*curr_framebuf;
	void		*xconn;
	void		*win;
	int			framebuf_sel;
	int			res[2];
}	t_x_data;

typedef	struct s_player
{
	t_point2d	dir;
	t_point2d	pos;
	t_point2d	cam_plane;
	float		fov_scale;
}	t_player;

typedef	struct s_keybindings
{
	t_actions	action;
	int			keysym;
}	t_keybindings;

typedef	struct s_input
{
	bool			actions[ACT_COUNT];
	t_keybindings	keybindings[ACT_COUNT * 2];
}	t_input;

typedef	struct s_data
{
	t_x_data	x_data;
	t_player	player;
	t_input		input;
	char		**map;
}	t_data;

typedef	struct s_render_facilities
{
	float		t_x;
	float		t_y;
	float		next_x;
	float		next_y;
	char		step_x;
	char		step_y;
	int			x;
	int			y;
	t_hit_type	hit;
	int			wall_height;
}	t_render_facilities;


//input
void	set_default_keybindings(t_keybindings *keybindings);
int		key_down(int keysym, t_input *input);
int		key_up(int keysym, t_input *input);
void	handle_keys(t_data *data);

//movement
void	rotate_player(t_player *player, float angle);
void	step_player(t_player *player, float step_size, enum direction dir);

//vector op-s
t_point2d	vec2d_sum(t_point2d p1, t_point2d p2);
t_point2d	vec2d_mul(t_point2d p1, float n);
t_point2d	vec2d_rotate_by_angle(t_point2d p1, float angle);
t_point2d	vec2d_normalize(t_point2d p1);

//draw routines
void	put_px_on_img(t_x_data *x_data, int x, int y, int color);
void	put_wall_bar_on_img(int x, int wall_height, int color, t_x_data *x_data);

//rendering
void	fill_render_info(t_render_facilities *rf, t_player *player, t_point2d *raydir);
void	cast_ray(t_data *data, t_point2d raydir, char **map, int x);
void	draw_frame(t_data *data);

//cleanup
void	free_data(t_data *data);
int		exit_handler(t_data *data);

//main game loop
int		game_loop(t_data *data);

#endif
