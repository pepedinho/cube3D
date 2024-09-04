/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:00:33 by itahri            #+#    #+#             */
/*   Updated: 2024/09/04 12:59:45 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	trace(double s_x, double s_y, double e_x, double e_y,
		t_map_data *map_data, int color)
{
	double	x_step;
	double	y_step;

	// printf("debug : start x : %f, start y : %f | to x : %f, to y : %f\n",
	//	s_x, s_y, e_x, e_y);
	x_step = abs_value((e_x - s_x) / 100);
	y_step = abs_value((e_y - s_y) / 100);
	if (s_x < e_x && s_y < e_y)
	{
		// printf("xstep == %f, ystep == %f\n", x_step, y_step);
		while (s_x < e_x && s_y < e_y)
		{
			s_x += x_step;
			s_y += y_step;
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, s_x * 64,
				s_y * 64, color);
		}
	}
	else if (s_x > e_x && s_y > e_y)
	{
		while (s_x > e_x || s_y > e_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, s_x * 64,
				s_y * 64, color);
			s_x -= x_step;
			s_y -= y_step;
		}
	}
}

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
			if (map[y][x] == '1' && x > 0)
				mlx_put_image_to_window(map_data->mlx->init,
					map_data->mlx->window, map_data->mlx->white_i, x * WIDTH, y
					* HEIGHT);
			else if (map[y][x] == '0' && x > 0)
				mlx_put_image_to_window(map_data->mlx->init,
					map_data->mlx->window, map_data->mlx->black_i, x * WIDTH, y
					* HEIGHT);
			x++;
		}
		y++;
	}
}
