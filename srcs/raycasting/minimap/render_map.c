/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:00:33 by itahri            #+#    #+#             */
/*   Updated: 2024/09/07 16:48:24 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"
#define CIRCLE_SCALE 32
#define MAP_SCALE 16

int	trace_perimeter(t_map_data *map_data, int r)
{
	double	h;
	double	k;
	double	radiant;
	int		i;
	int		x;
	int		y;

	i = 0;
	x = 5;
	y = 5;
	while (i < 5000)
	{
		radiant = 2 * M_PI * i / 5000;
		h = x + r * cos(radiant);
		k = y + r * sin(radiant);
		mlx_pixel_put(map_data->mlx.init, map_data->mlx.window, h
			* CIRCLE_SCALE, k * CIRCLE_SCALE, 0XFFFFFF);
		i++;
	}
	render_map(map_data);
	return (1);
}

int	map_ylen(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	trace_trait(t_map_data *map_data, double to_x, double to_y, int color)
{
	double	x_start;
	double	y_start;
	double	x_step;
	double	y_step;
	int		steps;
	int		i;

	x_start = 10.5;
	y_start = 10.5;
	steps = fmax(fabs(to_x - x_start), fabs(to_y - y_start)) * PRECISION;
	x_step = to_x * map_data->p_pos.dir_length;
	y_step = to_y * map_data->p_pos.dir_length;
	x_step /= steps;
	y_step /= steps;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(map_data->mlx.init, map_data->mlx.window, x_start
			* MAP_SCALE, y_start * MAP_SCALE, color);
		x_start += x_step;
		y_start += y_step;
		i++;
	}
}

void	render_map(t_map_data *map_data)
{
	int		x;
	int		y;
	char	**map;
	int		radius;
	int		px;
	int		py;
	int		draw_x;
	int		draw_y;

	radius = 8;
	py = map_data->p_pos.r_y;
	px = map_data->p_pos.r_x;
	y = py - radius;
	map = map_data->map;
	while (y <= py + radius)
	{
		if (y >= 0 && y < map_ylen(map))
		{
			x = px - radius;
			while (x <= px + radius)
			{
				if (x >= 0 && x <= ft_strlen(map[y]))
				{
					if ((x - px) * (x - px) + (y - py) * (y - py) <= radius
						* radius)
					{
						draw_x = 10 + (x - px);
						draw_y = 10 + (y - py);
						if (map[y][x] == '1')
						{
							// mlx_pixel_put(map_data->mlx.init,
							// 	map_data->mlx.window, draw_x * MAP_SCALE, draw_y
							// 	* MAP_SCALE, 0XFFFFFF);
							mlx_put_image_to_window(map_data->mlx.init,
								map_data->mlx.window, map_data->mlx.dot.img, 10
								* MAP_SCALE, 10 * MAP_SCALE);
							trace_trait(map_data, map_data->p_pos.direction.x,
								map_data->p_pos.direction.y, 0X0000FF);
							mlx_put_image_to_window(map_data->mlx.init,
								map_data->mlx.window, map_data->mlx.white.img,
								draw_x * MAP_SCALE, draw_y * MAP_SCALE);
						}
						else if (map[y][x] == 'D')
						{
							mlx_put_image_to_window(map_data->mlx.init,
								map_data->mlx.window, map_data->mlx.blue.img,
								draw_x * MAP_SCALE, draw_y * MAP_SCALE);
						}
					}
				}
				x++;
			}
		}
		y++;
	}
}
