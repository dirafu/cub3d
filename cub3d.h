#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <math.h>

# define RES_X 640
# define RES_Y 480
# define FOV 75

typedef struct s_x_data
{
	void		*xconn;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
}	t_x_data;

typedef	struct s_player
{
	float
};	t_player;



#endif
