/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_playable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:18:28 by madamou           #+#    #+#             */
/*   Updated: 2024/10/01 14:45:45 by madamou          ###   ########.fr       */
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
				|| map_data->map[y][x] == 'W' || map_data->map[y][x] == 'D')
			{
				if (ft_is_in_charset(map_data->map[y][x], "NSEW"))
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

int	check_next_cases_doors(char **map_cpy, int y, int x)
{
	if (map_cpy[y - 1][x] == '1' && map_cpy[y + 1][x] == '1' && !(map_cpy[y][x
			- 1] == '1' || map_cpy[y][x + 1] == '1') && !(map_cpy[y][x
			- 1] == 'D' || map_cpy[y][x + 1] == 'D'))
		return (1);
	if (map_cpy[y][x - 1] == '1' && map_cpy[y][x + 1] == '1' && !(map_cpy[y
			- 1][x] == '1' || map_cpy[y + 1][x] == '1') && !(map_cpy[y
			- 1][x] == 'D' || map_cpy[y + 1][x] == 'D'))
		return (1);
	return (0);
}

int	check_doors(t_map_data *map_data)
{
	int	x;
	int	y;

	y = -1;
	while (map_data->map[++y])
	{
		x = -1;
		while (map_data->map[y][++x])
		{
			if (map_data->map[y][x] == 'D')
			{
				if (!check_next_cases_doors(map_data->map, y, x))
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
		ft_putstr_fd("Error\nIncorrect map: Not close by wall\n", 2);
		destroy_mlx(data);
		return (0);
	}
	if (check_doors(data) == 0)
	{
		ft_putstr_fd("Error\nIncorrect map: Doors are not good\n", 2);
		destroy_mlx(data);
		return (0);
	}
	return (1);
}
