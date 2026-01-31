#include "cub3d.h"

t_point2d	vec2d_sum(t_point2d p1, t_point2d p2)
{
	t_point2d	tmp;

	tmp.x = p1.x + p2.x;
	tmp.y = p1.y + p2.y;
	return (tmp);
}

t_point2d	vec2d_mul(t_point2d p1, float n)
{
	t_point2d	tmp;

	tmp.x = p1.x * n;
	tmp.y = p1.y * n;
	return (tmp);
}

// t_point2d	vec2d_rotate(t_point2d p1, float angle)
// {
	
// }

// t_point2d	vec2d_normalize(t_point2d p1)
// {

// }
