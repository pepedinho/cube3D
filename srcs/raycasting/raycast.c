/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/04 13:05:18 by madamou          ###   ########.fr       */
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

	x_start = map_data->p_pos.r_x;
	y_start = map_data->p_pos.r_y;
	// printf("debug : start x : %f, start y : %f | to x : %f, to y : %f\n",
	//	x_start, y_start, to_x, to_y);
	x_step = abs_value((to_x - x_start) / 500);
	y_step = abs_value((to_y - y_start) / 500);
	if (x_start < to_x && y_start < to_y)
	{
		// printf("xstep == %f, ystep == %f\n", x_step, y_step);
		while (x_start < to_x && y_start < to_y)
		{
			x_start += x_step;
			y_start += y_step;
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* WIDTH, y_start * HEIGHT, color);
		}
	}
	else if (x_start > to_x && y_start > to_y)
	{
		while (x_start > to_x && y_start > to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* WIDTH, y_start * HEIGHT, color);
			x_start -= x_step;
			y_start -= y_step;
		}
	}
	else if (x_start > to_x && y_start < to_y)
	{
		while (x_start > to_x && y_start < to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* WIDTH, y_start * HEIGHT, color);
			x_start -= x_step;
			y_start += y_step;
		}
	}
	else if (x_start < to_x && y_start > to_y)
	{
		while (x_start < to_x && y_start > to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
				* WIDTH, y_start * HEIGHT, color);
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
	radiant = 66 * M_PI / 180;
	x1 = map_data->p_pos.r_x + r * cos(alpha);
	y1 = map_data->p_pos.r_y + r * sin(alpha);
	x2 = map_data->p_pos.r_x + r * cos(alpha + radiant);
	y2 = map_data->p_pos.r_y + r * sin(alpha + radiant);
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

int	dda(t_map_data *map_data, double angle)
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;

	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	map_x = (int)map_data->p_pos.r_x;
	map_y = (int)map_data->p_pos.r_y;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	hit = 0;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (map_data->p_pos.r_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - map_data->p_pos.r_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (map_data->p_pos.r_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - map_data->p_pos.r_y) * delta_dist_y;
	}
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		if (map_data->map[map_y][map_x] == '1')
			hit = 1;
	}
	trace_trait(map_data, map_x, map_y, 0XFF0000);
	return (1);
}

int	raycast(t_map_data *map_data, int r, double *start_end, int num_rays)
{
	double	increment;
	double	current_angle;
	int		i;

	(void)r;
	if (start_end[0] > start_end[1])
		increment = (2 * M_PI - start_end[0] + start_end[1]) / num_rays;
	i = 0;
	while (i < num_rays)
	{
		current_angle = start_end[0] + i * increment;
		if (current_angle >= 2 * M_PI)
			current_angle -= 2 * M_PI;
		dda(map_data, current_angle);
		i++;
	}
	free(start_end);
	return (1);
}

int	find_r(t_map_data *map_data)
{
	int	x;
	int	y;
	int	r;
	int	iterator;

	x = map_data->p_pos.b_x + 1;
	iterator = 1;
	while (map_data->map[map_data->p_pos.b_y][x] == '0')
	{
		x++;
		iterator++;
	}
	r = iterator;
	iterator = 0;
	y = map_data->p_pos.b_y + 1;
	while (map_data->map[y][map_data->p_pos.b_x] == '0')
	{
		y++;
		iterator++;
	}
	if (iterator > r)
		r = iterator;
	iterator = 0;
	x = map_data->p_pos.b_x - 1;
	while (x >= 0 && map_data->map[map_data->p_pos.b_y][x] == '0')
	{
		x--;
		iterator++;
	}
	if (iterator > r)
		r = iterator;
	iterator = 0;
	y = map_data->p_pos.b_y - 1;
	while (y >= 0 && map_data->map[y][map_data->p_pos.b_x] == '0')
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
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window,
		map_data->p_pos.r_x * WIDTH, map_data->p_pos.r_y * HEIGHT, 0XFF0000);
	while (i < 5000)
	{
		radiant = 2 * M_PI * i / 5000;
		h = map_data->p_pos.r_x + r * cos(radiant);
		k = map_data->p_pos.r_y + r * sin(radiant);
		mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, h * WIDTH, k
			* HEIGHT, 0XFFFFFF);
		i++;
	}
	raycast(map_data, find_r(map_data), define_fov(map_data, find_r(map_data),
			alpha), 1500);
	return (1);
}
