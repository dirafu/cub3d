/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:37:06 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/19 21:01:59 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

int	main_verif(int argc, char **argv, t_verif *v)
{
	// t_verif	v;
	int		fd;

	// ft_memset(&v, 0, sizeof(*v));
	if (argc != 2)
		return (printf("Wrong no. of arguments!\n"), 1);
	if (arg_check(argv[1]))
		return (printf("Arg validation failed!\n"), 1);
	if (pre_map_structure_checker(argv[1], v, &fd))
		return (struct_destroyer(v), 1);
	if (pre_map_content_checker(v))
		return (struct_destroyer(v), 1);
	if (map_check(v, &fd))
		return (struct_destroyer(v), gnl_drain(&fd), 1);
	printf("Arg & map validated\n");
	printf("Dimensions: %i by %i\n", v->rows, v->cols);
	printf("Player position X: %i, Y:%i\n", v->pos_x, v->pos_y);
	return (0);
}
