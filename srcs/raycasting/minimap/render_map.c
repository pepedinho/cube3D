/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:00:33 by itahri            #+#    #+#             */
/*   Updated: 2024/09/04 16:47:50 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	render_map(t_map_data *map_data)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = map_data->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				mlx_put_image_to_window(map_data->mlx->init,
					map_data->mlx->window, map_data->mlx->white_i, x * WIDTH, y
					* HEIGHT);
				mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x
					* WIDTH, y * HEIGHT, 0XFF0000);
			}
			else if (map[y][x] == '0')
				mlx_put_image_to_window(map_data->mlx->init,
					map_data->mlx->window, map_data->mlx->black_i, x * WIDTH, y
					* HEIGHT);
			x++;
		}
		y++;
	}
}
