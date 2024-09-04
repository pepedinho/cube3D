/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:00:33 by itahri            #+#    #+#             */
/*   Updated: 2024/09/04 16:46:59 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	render_map(t_map_data *map_data)
{
	int		x;
	int		y;
	int len_x;
	int len_y;
	char	**map;

	y = 0;
	len_x = len_bigest_line(map_data->map) / 2;
	len_y = ft_strlen_2d(map_data->map) / 2;
	map = map_data->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				mlx_put_image_to_window(map_data->mlx->init,
					map_data->mlx->window, map_data->mlx->white_i, x * WIDTH, y
					* HEIGHT);
			else if (map[y][x] == '0')
				mlx_put_image_to_window(map_data->mlx->init,
					map_data->mlx->window, map_data->mlx->black_i, x * WIDTH / len_x, y
					* HEIGHT / len_y);
			x++;
		}
		y++;
	}
}
