/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:09:37 by vlchinen          #+#    #+#             */
/*   Updated: 2025/02/22 18:15:49 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>

# include <unistd.h>

# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

typedef struct s_lst
{
	int				*fd;
	char			*content;
	struct s_lst	*prev;
	struct s_lst	*next;
}	t_lst;

char	*get_next_line(int fd);

char	*pick_a_line(char *file);

char	*trim_fst_line(char *file, char *smth, int mode);

char	*read_buff_and_join_file(int fd, char *buff, t_lst *lst, int fs);

char	*join_line(t_lst *lst, char *buff, char *file);

int		search_for_nl(char *str);

size_t	ft_strlen(char *str);

t_lst	*search_lst(t_lst *lst, int fd);

void	*del_or_append_node(t_lst **lst, t_lst *node, int mode);

t_lst	*new_node(char *content, int fd);

#endif
