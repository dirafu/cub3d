/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <vlchinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 02:09:24 by ikiriush          #+#    #+#             */
/*   Updated: 2026/04/19 22:07:35 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERIF_H
# define VERIF_H

# include "../cub3d.h"

typedef struct s_verif t_verif;

int		arg_check(char *argv);
int		col_counter(char **map);
int		door_checker(char **map, int i, int j);
int		ft_safe_atoi(const char *str);
void	freer(char **buf, char ***argv);
int		ft_realloc(char ***ptr, size_t old_size);
void	gnl_drain(int *fd);
int		map_char_checker(t_verif *v, char *buf, int *i, int n);
int		map_check(t_verif *v, int *fd);
int		pre_map_structure_checker(char *argv, t_verif *v, int *fd);
int		pre_map_content_checker(t_verif *v);
int		row_checker(char **map);
int		row_counter(char **map);
int		space_zero_crosscheker(char **map, int i, int j);
void	struct_destroyer(t_verif *v);

#endif