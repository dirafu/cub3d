/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_verif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikiriush <ikiriush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:37:06 by ikiriush          #+#    #+#             */
/*   Updated: 2026/05/06 04:08:46 by ikiriush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verif.h"

int	main_verif(int argc, char **argv, t_verif *v)
{
	int		fd;

	if (argc != 2)
		return (printf("Wrong no. of arguments!\n"), 1);
	if (arg_check(argv[1]))
		return (printf("Invalid arguments!\n"), 1);
	if (pre_map_structure_checker(argv[1], v, &fd))
		return (struct_destroyer(v), 1);
	if (pre_map_content_checker(v))
		return (struct_destroyer(v), 1);
	if (map_check(v, &fd))
		return (struct_destroyer(v), gnl_drain(&fd), 1);
	return (0);
}
