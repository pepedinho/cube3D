/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_playable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:18:28 by madamou           #+#    #+#             */
/*   Updated: 2024/09/01 22:46:13 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

int	check_next_cases(char **map_cpy, int y, int x)
{
	int	cpt;

	cpt = 0;
	if (y == 0 || x == 0)
		return (0);
	if (x == ft_strlen(map_cpy[y]) || y == ft_strlen_2d(map_cpy))
		return (0);
	if (map_cpy[y + 1][x] == ' ' || map_cpy[y + 1][x] == '\0')
		return (0);
	if (map_cpy[y - 1][x] == ' ' || map_cpy[y - 1][x] == '\0')
		return (0);
	if (map_cpy[y][x + 1] == ' ' || map_cpy[y][x + 1] == '\0')
		return (0);
	if (map_cpy[y][x - 1] == ' ' || map_cpy[y][x + 1] == '\0')
		return (0);
	return (1);
}

int	check_the_map(char **map_cpy)
{
	int	x;
	int	y;

	y = 0;
	while (map_cpy[y])
	{
		x = 0;
		while (map_cpy[y][x])
		{
			if (map_cpy[y][x] == '0' || map_cpy[y][x] == 'N'
				|| map_cpy[y][x] == 'S' || map_cpy[y][x] == 'E'
				|| map_cpy[y][x] == 'W')
			{
				if (!check_next_cases(map_cpy, y, x))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_playable(t_map_data *data)
{
	if (check_the_map(data->map) == 0)
		return (0);
	print_2d_array(data->map);
	return (1);
}
