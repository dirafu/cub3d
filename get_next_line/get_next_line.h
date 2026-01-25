/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:48:49 by vlchinen          #+#    #+#             */
/*   Updated: 2025/02/21 11:58:27 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

# include <unistd.h>

# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

char	*pick_a_line(char *file);

char	*trim_fst_line(char *file);

char	*read_buff_and_join_file(int fd, char *buff, char *file);

char	*join_line(char *file, char *buff);

int		search_for_nl(char *str);

size_t	ft_strlen_gnl(char *str);

char	*ft_strdup_gnl(char *str);

void	free_buff_and_file(char *buff, char *file);

#endif
