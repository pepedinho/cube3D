/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/03 20:12:31 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycatsing.h"

double	abs_value(double nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}

void	trace_trait(t_map_data *map_data, double to_x, double to_y, int color)
{
	double	x_start;
	double	y_start;
	double	x_step;
	double	y_step;

	x_start = map_data->p_pos.x;
	y_start = map_data->p_pos.y;
	// printf("debug : start x : %f, start y : %f | to x : %f, to y : %f\n",
	//	x_start, y_start, to_x, to_y);
	x_step = abs_value((to_x - x_start) / 100);
	y_step = abs_value((to_y - y_start) / 100);
	if (x_start < to_x && y_start < to_y)
	{
		// printf("xstep == %f, ystep == %f\n", x_step, y_step);
		while (x_start < to_x && y_start < to_y)
		{
			x_start += x_step;
			y_start += y_step;
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* 64, y_start * 64, color);
		}
	}
	else if (x_start > to_x && y_start > to_y)
	{
		while (x_start > to_x || y_start > to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* 64, y_start * 64, color);
			x_start -= x_step;
			y_start -= y_step;
		}
	}
	else if (x_start > to_x && y_start < to_y)
	{
		while (x_start > to_x || y_start < to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* 64, y_start * 64, color);
			x_start -= x_step;
			y_start += y_step;
		}
	}
	else if (x_start < to_x && y_start > to_y)
	{
		while (x_start < to_x && y_start > to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* 64, y_start * 64, color);
			x_start += x_step;
			y_start -= y_step;
		}
	}
}

double	*define_fov(t_map_data *map_data, int r, double alpha)
{
	double	radiant;
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double	*angles;

	angles = malloc(sizeof(double) * 2);
	radiant = 80 * M_PI / 180;
	x1 = map_data->p_pos.x + r * cos(alpha);
	y1 = map_data->p_pos.y + r * sin(alpha);
	x2 = map_data->p_pos.x + r * cos(alpha + radiant);
	y2 = map_data->p_pos.y + r * sin(alpha + radiant);
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x1 * 64, y1 * 64,
		0X008000);
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x2 * 64, y2 * 64,
		0X008000);
	// printf("fov1 ==  : (%f, %f)\n", x1, y1);
	// printf("fov2 ==  : (%f, %f)\n", x2, y2);
	trace_trait(map_data, x1, y1, 0XFFFF00);
	trace_trait(map_data, x2, y2, 0X008000);
	angles[0] = alpha;
	angles[1] = alpha + radiant;
	if (angles[1] > 2 * M_PI)
		angles[1] -= 2 * M_PI;
	return (angles);
}

/*
 * first condition in loop check if the current angle is in the FOV range
 * |
 * --->(radiant >= start_end[0] && radiant <= start_end[1])
 *

	*  second condition is in the case of beggining angle is bigger than finish angle
 *  |
 *  --->(start_end[0] > start_end[1] && (radiant >= start_end[0]
 *        ||   radiant <= start_end[1])
 */

int	raycast(t_map_data *map_data, int r, double *start_end)
{
	double	h;
	double	k;
	double	radiant;
	int		i;

	i = 0;
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, map_data->p_pos.x
		* 64, map_data->p_pos.y * 64, 0XFF0000);
	while (i < 150)
	{
		radiant = 2 * M_PI * i / 150;
		h = map_data->p_pos.x + r * cos(radiant);
		k = map_data->p_pos.y + r * sin(radiant);
		if (radiant >= start_end[0] && radiant <= start_end[1])
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, h * 64, k
				* 64, 0XFF0000);
			trace_trait(map_data, h, k, 0XFF0000);
		}
		else if (start_end[0] > start_end[1] && (radiant >= start_end[0]
				|| radiant <= start_end[1]))
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, h * 64, k
				* 64, 0XFF0000);
			trace_trait(map_data, h, k, 0XFF0000);
		}
		i++;
	}
	return (1);
}

int	find_r(t_map_data *map_data)
{
	int	x;
	int	y;
	int	r;
	int	iterator;

	x = map_data->p_pos.x + 1;
	iterator = 1;
	while (map_data->map[map_data->p_pos.y][x] == '0')
	{
		x++;
		iterator++;
	}
	r = iterator;
	iterator = 0;
	y = map_data->p_pos.y + 1;
	while (map_data->map[y][map_data->p_pos.x] == '0')
	{
		y++;
		iterator++;
	}
	if (iterator > r)
		r = iterator;
	iterator = 0;
	x = map_data->p_pos.x - 1;
	while (x >= 0 && map_data->map[map_data->p_pos.y][x] == '0')
	{
		x--;
		iterator++;
	}
	if (iterator > r)
		r = iterator;
	iterator = 0;
	y = map_data->p_pos.y - 1;
	while (y >= 0 && map_data->map[y][map_data->p_pos.x] == '0')
	{
		y--;
		iterator++;
	}
	if (iterator > r)
		r = iterator;
	return (r);
}

int	trace_perimeter(t_map_data *map_data, int r, double alpha)
{
	double	h;
	double	k;
	double	radiant;
	int		i;

	i = 0;
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, map_data->p_pos.x
		* 64, map_data->p_pos.y * 64, 0XFF0000);
	while (i < 5000)
	{
		radiant = 2 * M_PI * i / 5000;
		h = map_data->p_pos.x + r * cos(radiant);
		k = map_data->p_pos.y + r * sin(radiant);
		mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, h * 64, k
			* 64, 0XFFFFFF);
		i++;
	}
	raycast(map_data, find_r(map_data), define_fov(map_data, find_r(map_data),
			alpha));
	return (1);
}
