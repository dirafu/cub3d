/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_with_leading_zeroes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlchinen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:23:23 by vlchinen          #+#    #+#             */
/*   Updated: 2025/01/25 20:40:08 by vlchinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_with_leading_zeroes_pt2(char *num_str, size_t num_init_len, size_t width, char *padded_num_str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (num_str[0] == '-' && ++i && ++width && ++j)
		padded_num_str[0] = '-';
	while (i < width - num_init_len)
	{
		padded_num_str[i] = '0';
		i++;
	}
	while (num_str[j])
	{
		padded_num_str[i] = num_str[j];
		j++;
		i++;
	}
	padded_num_str[i] = '\0';
	free(num_str);
}

char	*ft_itoa_with_leading_zeroes(int num, size_t width)
{
	char	*num_str;
	char	*padded_num_str;
	size_t	num_init_len;

	num_str = ft_itoa(num);
	if (!num_str)
		return (NULL);
	num_init_len = ft_strlen(num_str);
	if (num_init_len >= width)
		return (num_str);
	padded_num_str = malloc(sizeof(char) * (width + 1));
	if (!padded_num_str)
		return (free(num_str), NULL);
	ft_itoa_with_leading_zeroes_pt2(num_str, num_init_len, width, padded_num_str);
	return (padded_num_str);
}
