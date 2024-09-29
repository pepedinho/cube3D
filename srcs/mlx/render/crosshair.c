/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:27:25 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 03:27:54 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	draw_crosshair_x(t_map_data *data, int center_x, int center_y, int size)
{
	int		x;
	char	*target;

	x = center_x - size;
	while (x <= center_x + size)
	{
		if (x >= 0 && x < data->mlx.width && (x < center_x - 3 || x > center_x
				+ 3))
		{
			target = data->mlx.img.adrr + (center_y * data->mlx.img.size_line
					+ x * (data->mlx.img.bits_per_pixel_div8));
			*(unsigned int *)target = WHITE;
		}
		x++;
	}
}

void	draw_crosshair_y(t_map_data *data, int center_x, int center_y, int size)
{
	int		y;
	char	*target;

	y = center_y - size;
	while (y <= center_y + size)
	{
		if (y >= 0 && y < data->mlx.height && (y < center_y - 3 || y > center_y
				+ 3))
		{
			target = data->mlx.img.adrr + (y * data->mlx.img.size_line
					+ center_x * (data->mlx.img.bits_per_pixel_div8));
			*(unsigned int *)target = WHITE;
		}
		y++;
	}
}

void	display_crosshair(t_map_data *data)
{
	int	center_x;
	int	center_y;
	int	size;

	center_x = data->mlx.width / 2;
	center_y = data->mlx.height / 2;
	size = 10;
	draw_crosshair_x(data, center_x, center_y, size);
	draw_crosshair_y(data, center_x, center_y, size);
}
