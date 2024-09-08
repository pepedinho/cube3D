/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_playable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:18:28 by madamou           #+#    #+#             */
/*   Updated: 2024/09/08 12:23:54 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

int	check_next_cases(char **map_cpy, int y, int x)
{
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

int	check_the_map(t_map_data *map_data)
{
	int	x;
	int	y;

	y = -1;
	while (map_data->map[++y])
	{
		x = -1;
		while (map_data->map[y][++x])
		{
			if (map_data->map[y][x] == '0' || map_data->map[y][x] == 'N'
				|| map_data->map[y][x] == 'S' || map_data->map[y][x] == 'E'
				|| map_data->map[y][x] == 'W')
			{
				if (map_data->map[y][x] != '0')
				{
					map_data->p_pos.r_x = x;
					map_data->p_pos.r_y = y;
				}
				if (!check_next_cases(map_data->map, y, x))
					return (0);
			}
		}
	}
	return (1);
}

int	check_map_playable(t_map_data *data)
{
	if (check_the_map(data) == 0)
	{
		ft_fprintf(2, "Error\nIncorrect map\n");
		return (0);
	}
	return (1);
}
