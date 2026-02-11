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

t_point2d	vec2d_rotate_by_angle(t_point2d p1, float angle)
{
	float	cosa;
	float	sina;
	float	p1_x;

	cosa = cosf(angle * (M_PI / 180.0f));
	sina = sinf(angle * (M_PI / 180.0f));
	p1_x = p1.x;
	p1.x = p1.x * cosa - p1.y * sina;
	p1.y = p1_x * sina + p1.y * cosa;
	return (p1);
}

t_point2d	vec2d_normalize(t_point2d p1)
{
	float	len;

	len = sqrtf((p1.x * p1.x) + (p1.y * p1.y));
	p1.x /= len;
	p1.y /= len;
	return (p1);
}
