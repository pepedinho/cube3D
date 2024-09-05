/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/05 01:56:30 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycatsing.h"

#define PRECISION 50

void	trace_trait(t_map_data *map_data, double to_x, double to_y, int color)
{
	double	x_start;
	double	y_start;
	double	x_step;
	double	y_step;
	int		steps;
	int		i;

	x_start = map_data->p_pos.r_x;
	y_start = map_data->p_pos.r_y;
	steps = fmax(fabs(to_x - x_start), fabs(to_y - y_start)) * PRECISION;
	x_step = (to_x - x_start) / steps;
	y_step = (to_y - y_start) / steps;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
			* WIDTH, y_start * HEIGHT, color);
		x_start += x_step;
		y_start += y_step;
		i++;
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
	if (angles[0] > 2 * M_PI)
		angles[0] -= 2 * M_PI;
	return (angles);
}

int	sign(double nb)
{
	if (nb < 0)
		return (-1);
	return (1);
}

double	set_side_dist(double ray_dir, double pos, int map, double delta)
{
	if (ray_dir < 0)
		return ((pos - map) * delta);
	return ((map + 1.0 - pos) * delta);
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
	double	ray_length;
	int		step_x;
	int		step_y;
	int		hit;

	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	// printf("ray_dix_x == %f || ray_dir_y == %f\n", ray_dir_x, ray_dir_y);
	map_x = (int)map_data->p_pos.r_x;
	map_y = (int)map_data->p_pos.r_y;
	hit = 0;
	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);
	step_x = sign(ray_dir_x);
	step_y = sign(ray_dir_y);
	side_dist_x = set_side_dist(ray_dir_x, map_data->p_pos.b_x, map_x,
			delta_dist_x);
	side_dist_y = set_side_dist(ray_dir_y, map_data->p_pos.b_y, map_y,
			delta_dist_y);
	while (hit == 0)
	{
		printf("\n\nmap_x: %d, map_y: %d, side_dist_x: %f, side_dist_y:%f\n",
			map_x, map_y, side_dist_x, side_dist_y);
		printf("actuel case == %c\n\n", map_data->map[map_y][map_x]);
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
	if (side_dist_x < side_dist_y)
		ray_length = side_dist_x - delta_dist_x;
	else
		ray_length = side_dist_y - delta_dist_y;
	trace_trait(map_data, map_x, map_y, 0XFF0000);
	return (1);
}

int	raycast(t_map_data *map_data, int r, double *start_end, int num_rays)
{
	double	increment;
	double	current_angle;
	int		i;

	(void)r;
	increment = (start_end[1] - start_end[0]) / num_rays;
	if (start_end[0] > start_end[1])
		increment = (2 * M_PI - start_end[0] + start_end[1]) / num_rays;
	i = 0;
	while (i < num_rays)
	{
		if (i > 0)
			current_angle = start_end[0] + i * increment;
		if (current_angle >= 2 * M_PI)
			current_angle -= 2 * M_PI;
		dda(map_data, current_angle);
		i++;
	}
	free(start_end);
	return (1);
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
	raycast(map_data, 3, define_fov(map_data, 3, alpha), 1500);
	return (1);
}
