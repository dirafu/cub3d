/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <vlchinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:50:37 by vlchinen          #+#    #+#             */
/*   Updated: 2026/05/07 16:53:33 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	static t_data	data;
	static t_verif	verif;

	if (main_verif(argc, argv, &verif))
		return (1);
	data.verif = &verif;
	if (!init(&data, &verif) || !read_resources(&data, &verif))
		return (free_data(&data), print_error(), 1);
	hook_up(&data);
}
