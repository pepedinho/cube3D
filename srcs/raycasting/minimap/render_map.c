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
		mlx_pixel_put(map_data->mlx.init, map_data->mlx.window, h * WIDTH, k
			* HEIGHT, 0XFFFFFF);
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

	x_start = 5;
	y_start = 5;
	steps = fmax(fabs(to_x - x_start), fabs(to_y - y_start)) * PRECISION;
	x_step = (to_x - x_start) / steps;
	y_step = (to_y - y_start) / steps;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(map_data->mlx.init, map_data->mlx.window, x_start * WIDTH,
			y_start * HEIGHT, color);
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

	radius = 4;
	py = map_data->p_pos.r_y;
	px = map_data->p_pos.r_x;
	y = py - radius;
	map = map_data->map;
	while (y <= py + radius)
	{
		if (y >= 0 && y <= map_ylen(map))
		{
			x = px - radius;
			while (x <= px + radius)
			{
				if (x >= 0 && x <= ft_strlen(map[y]))
				{
					if ((x - px) * (x - px) + (y - py) * (y - py) <= radius
						* radius)
					{
						if (map[y][x] == '1')
						{
							draw_x = 5 + (x - px);
							draw_y = 5 + (y - py);
							mlx_pixel_put(map_data->mlx.init,
								map_data->mlx.window, 5 * WIDTH, 5 * HEIGHT,
								0XFFFFFF);
							trace_trait(map_data, map_data->p_pos.dir_y,
								map_data->p_pos.dir_y, 0XFFFFFF);
							mlx_put_image_to_window(map_data->mlx.init,
								map_data->mlx.window, map_data->mlx.white.img,
								draw_x * WIDTH, draw_y * HEIGHT);
						}
					}
				}
				x++;
			}
		}
		y++;
	}
}
