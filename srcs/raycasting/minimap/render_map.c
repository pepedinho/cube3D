/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:00:33 by itahri            #+#    #+#             */
/*   Updated: 2024/09/29 06:20:22 by madamou          ###   ########.fr       */
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

	i = 0;
	while (i < 5000)
	{
		radiant = 2 * M_PI * i / 5000;
		h = 5 + r * cos(radiant);
		k = 5 + r * sin(radiant);
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
	t_vec	start;
	double	x_step;
	double	y_step;
	int		steps;
	int		i;

	start.x = 10.5;
	start.y = 10.5;
	steps = fmax(fabs(to_x - start.x), fabs(to_y - start.y)) * PRECISION;
	x_step = to_x * map_data->p_pos.dir_length;
	y_step = to_y * map_data->p_pos.dir_length;
	x_step /= steps;
	y_step /= steps;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(map_data->mlx.init, map_data->mlx.window, start.x
			* MAP_SCALE, start.y * MAP_SCALE, color);
		start.x += x_step;
		start.y += y_step;
		i++;
	}
}

void	render_map(t_map_data *map_data)
{
	int			x;
	int			y;
	char		**map;
	int			radius;
	t_vecint	p;
	t_vecint	draw;

	radius = 8;
	p.y = map_data->p_pos.r_y;
	p.x = map_data->p_pos.r_x;
	y = p.y - radius;
	map = map_data->map;
	while (y <= p.y + radius)
	{
		if (y >= 0 && y < map_ylen(map))
		{
			x = p.x - radius;
			while (x <= p.x + radius)
			{
				if (x >= 0 && x <= ft_strlen(map[y]))
				{
					if ((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y) <= radius
						* radius)
					{
						draw.x = 10 + (x - p.x);
						draw.y = 10 + (y - p.y);
						if (map[y][x] == '1')
						{
							// mlx_pixel_put(map_data->mlx.init,
							// 	map_data->mlx.window, draw.x * MAP_SCALE, draw.y
							// 	* MAP_SCALE, 0XFFFFFF);
							mlx_put_image_to_window(map_data->mlx.init,
								map_data->mlx.window, map_data->mlx.dot.img, 10
								* MAP_SCALE, 10 * MAP_SCALE);
							trace_trait(map_data, map_data->p_pos.direction.x,
								map_data->p_pos.direction.y, 0X0000FF);
							mlx_put_image_to_window(map_data->mlx.init,
								map_data->mlx.window, map_data->mlx.white.img,
								draw.x * MAP_SCALE, draw.y * MAP_SCALE);
						}
						else if (map[y][x] == 'D')
						{
							mlx_put_image_to_window(map_data->mlx.init,
								map_data->mlx.window, map_data->mlx.blue.img,
								draw.x * MAP_SCALE, draw.y * MAP_SCALE);
						}
					}
				}
				x++;
			}
		}
		y++;
	}
}
