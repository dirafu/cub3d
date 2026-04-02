#ifndef CUB3D_H
# define CUB3D_H

# define _DEFAULT_SOURCE
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <stdint.h>
# include <sys/time.h>

# define RES_X 640
# define RES_Y 480
# define FOV 55
# define MAX_SIMULTANEOUS_KEYS 10
# define PLAYER_RADIUS 0.1f
# define A_FRAME_DUR_U 1000000 * 0.2f
# define DOOR_AUTO_CLOSE_T 1000000 * 5

typedef enum actions
{
	ACT_LEFT,
	ACT_RIGHT,
	ACT_FORWARD,
	ACT_BACKWARD,
	ACT_STRAFE_LEFT,
	ACT_STRAFE_RIGHT,
	ACT_OPEN_DOOR,
	ACT_COUNT
}	t_actions;

typedef enum hit_type
{
	HIT_NORTH = 0,
	HIT_WEST,
	HIT_SOUTH,
	HIT_EAST,
	HIT_NONE,
	VERTICAL,
	HORIZONTAL,
}	t_hit_type;

typedef enum
{
	WALL_TEX_N = 0,
	WALL_TEX_W,
	WALL_TEX_S,
	WALL_TEX_E,
	WALL_TEX_COUNT
}	t_wall_tex_enum;

typedef enum
{
	DOOR_TEX_FACE = 0,
	DOOR_TEX_SIDE,
	DOOR_TEX_COUNT
}	t_door_tex_enum;

enum	direction
{
	PARALLEL,
	PERPENDICULAR
};

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
	int			res_x;
	int			res_y;
}	t_img_data;

//array of all the loaded sprites variations (in data->sprites_animations)
typedef	struct s_sprite_animation
{
	t_img_data		*frames;
	size_t			num_of_frames;
	uint64_t		frame_duration;
}	t_sprite_animation;

//array of all the individual sprites on the map (in data->sprites)
typedef	struct s_sprite
{
	t_sprite_animation	*animation;
	t_point2d			pos;
	uint64_t			last_update_t;
	size_t				curr_frame;
}	t_sprite;

//array of t_sprite * sorted by Y coord with transformed coordinates relative to player pos
typedef	struct s_sprite_rendering_view
{
	t_sprite			*sprite;
	t_point2d			pos_transformed;
	float				projected_x;
}	t_sprite_rendering_view;

//animation is stored in ./{"$dir"} directory and named like frame number + ".xpm" with leading zeroes;
//e.g. from 00.xpm to 41.xpm in case num_of_frames is 42
typedef	struct s_animated_sprites_info
{
	size_t	num_of_frames;
	char	*dir;
	char	sprite_id;
}	t_animated_sprites_info;

typedef struct s_x_data
{
	t_img_data	img_data[2];
	t_img_data	*curr_framebuf;
	float		zbuff[RES_X];
	void		*xconn;
	void		*win;
	int			framebuf_sel;
	int			res[2];
}	t_x_data;

typedef enum
{
	CELL_TERMINATOR = 0,
	CELL_WALL,
	CELL_EMPTY,
	CELL_DOOR,
	CELL_SPRITE,
	CELL_NONE
}	t_map_cell_type;

typedef	enum
{
	DOOR_STATUS_CLOSED = 0,
	DOOR_STATUS_OPENED,
	DOOR_STATUS_CLOSING,
	DOOR_STATUS_OPENING
}	t_door_status;

typedef	struct s_map
{
	t_map_cell_type		type;
	t_sprite			*sprite;
	float				door_open_factor;
	t_door_status		door_status;
	uint64_t			door_open_time;
	int					door_orientation;
	char				sprite_id;
}	t_map;

typedef	struct s_player
{
	t_point2d	dir;
	t_point2d	pos;
	t_point2d	cam_plane;
	t_point2d	cam_plane_normalized;
	float		radius;
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

typedef	struct s_time_data
{
	double		time_d;
	uint64_t	last_frame_time;
}	t_time_data;

typedef	struct s_data
{
	t_time_data				time_data;
	t_x_data				x_data;
	t_player				player;
	t_input					input;
	t_img_data				wall_textures[WALL_TEX_COUNT];
	t_img_data				door_textures[DOOR_TEX_COUNT];
	t_sprite_animation		*sprites_animations;
	t_sprite				*sprites;
	t_sprite_rendering_view	*sprites_zsorted;
	t_map					**map;
	t_map					**active_doors;
	size_t					active_doors_count;
	int						ceiling_color;
	int						floor_color;
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
	int			overall_number_of_steps;
	float		tex_x;
	bool		door_plate;
	t_map		*passed_door;
	int			door_x;
	int			door_y;
}	t_render_facilities;

//input
void	set_default_keybindings(t_keybindings *keybindings);
int		key_down(int keysym, t_input *input);
int		key_up(int keysym, t_input *input);
void	handle_keys(t_data *data);
int		handle_mouse(int x, int y, t_data *data);

//movement
void	rotate_player(t_player *player, float angle);
void	step_player(t_player *player, t_map **map, float step_size, enum direction dir);

//vector op-s
t_point2d	vec2d_sum(t_point2d p1, t_point2d p2);
t_point2d	vec2d_sub(t_point2d p1, t_point2d p2);
t_point2d	vec2d_mul(t_point2d p1, float n);
t_point2d	vec2d_rotate_by_angle(t_point2d p1, float angle);
t_point2d	vec2d_normalize(t_point2d p1);

//draw routines
void	put_px_on_img(t_x_data *x_data, int x, int y, int color);
void	put_wall_bar_on_img(int x, t_data *data, t_render_facilities *rf);
int		get_img_px_color(t_img_data *image, int x, int y);

//rendering
void	fill_render_info(t_render_facilities *rf, t_player *player, t_point2d *raydir);
int		get_texture_pixel(int wall_y, t_data *data, t_render_facilities *rf, t_img_data *tx);
bool	draw_door(int x, t_data *data, t_render_facilities *rf_o, t_point2d raydir);
float	get_hit_dist(t_render_facilities *rf);
void	do_step(t_point2d *raydir, t_render_facilities *rf);
void	cast_ray(t_data *data, t_point2d raydir, int x);
void	draw_frame(t_data *data);
void	draw_walls(t_data *data);
void	draw_sprites(t_data *data);

//cleanup
void	free_data(t_data *data);
int		exit_handler(t_data *data);
void	free_textures(t_data *data);
void	free_xdata(t_data *data);
void	free_map(t_data *data);
void	free_sprites_array(t_data *data);

//main game loop
int		game_loop(t_data *data);

//misc
uint64_t	ft_get_time_us(void);
void		print_error();
size_t		count_map_cells(t_map **map, t_map_cell_type type);

//textures initialization
bool	read_resources(t_data *data);
bool	read_sprites(t_data *data);
bool	read_wall_textures(t_data *data);
char	*get_full_frame_filename(char *dir, size_t num_width, size_t frame_num);

//other init
bool					init(t_data *data);
bool					x_init(t_x_data *data);
t_sprite_rendering_view	*alloc_zsorted(t_data *data);

t_map	**test_mock_map_structure_prep(char **map);

#endif
