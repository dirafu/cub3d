#include "libft.h"

float	ft_lerp(float a, float b, float t)
{
	return (a * (1.0 - t) + b * t);
}