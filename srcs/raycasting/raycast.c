/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/02 19:16:38 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycatsing.h"

double abs_value(double nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}

void trace_trait(t_map_data *map_data, double to_x, double to_y, int color)
{
	double x_start;
	double y_start;
	double x_step;
	double y_step;


	x_start = map_data->p_pos.x;
	y_start = map_data->p_pos.y;
	printf("debug : start x : %f, start y : %f | to x : %f, to y : %f\n", x_start, y_start, to_x, to_y);
	x_step = abs_value((to_x - x_start) / 100);
	y_step = abs_value((to_y - y_start) / 100);
	if (x_start < to_x && y_start < to_y)
	{
		printf("xstep == %f, ystep == %f\n", x_step, y_step);
		while (x_start < to_x && y_start < to_y)
		{
			x_start += x_step;
			y_start += y_step;
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start * 64, y_start * 64, color);
		}
	}
	else if (x_start > to_x && y_start > to_y)
	{
		while (x_start > to_x || y_start > to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start * 64, y_start * 64, color);
			x_start -= x_step;
			y_start -= y_step;
		}
	}
	else if (x_start > to_x && y_start < to_y)
	{
		while (x_start > to_x || y_start < to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start * 64, y_start * 64, color);
			x_start -= x_step;
			y_start += y_step;	
		}
	}
	else if (x_start < to_x && y_start > to_y)
	{
		while (x_start < to_x && y_start > to_y)
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start * 64, y_start * 64, color);
			x_start += x_step;
			y_start -= y_step;	
		}
	}
}

double	*define_fov(t_map_data *map_data, int r)
{
	double	radiant;
	double	alpha;
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	double *tab;

	tab = malloc(sizeof(double) * 2);
	alpha = 90;
	radiant = 80 * M_PI / 180;
	x1 = map_data->p_pos.x + r * cos(alpha);
	y1 = map_data->p_pos.y + r * sin(alpha);
	x2 = map_data->p_pos.x + r * cos(alpha + radiant);
	y2 = map_data->p_pos.y + r * sin(alpha + radiant);
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x1 * 64, y1 * 64, 0X008000);
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x2 * 64, y2 * 64, 0X008000);
	printf("fov1 ==  : (%f, %f)\n", x1, y1);
	printf("fov2 ==  : (%f, %f)\n", x2, y2);
	trace_trait(map_data, x1, y1, 0X008000);
	trace_trait(map_data, x2, y2, 0X008000);
	tab[0] = x1;
	tab[1] = y2; 
	return (tab);
}
int	raycast(t_map_data *map_data, int r, double *start_end)
{
	double	h;
	double	k;
	double	radiant;
	int		i;

	i = 0;
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, map_data->p_pos.x * 64, map_data->p_pos.y * 64, 0XFF0000);
	while (i < 150)
	{
		radiant = 2 * M_PI * i / 150;
		h = map_data->p_pos.x + r * cos(radiant);
		k = map_data->p_pos.y + r * sin(radiant);
		if (h <= start_end[0] && k >= start_end[1])
		{
			mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, h * 64, k * 64, 0XFF0000);
			trace_trait(map_data, h, k, 0XFF0000);
			printf("DBUEFVIBGKDKJB\n");
		}
		i++;
	}
	return (1);
}

int	trace_perimeter(t_map_data *map_data, int r)
{
	double	h;
	double	k;
	double	radiant;
	int		i;

	i = 0;
	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, map_data->p_pos.x * 64, map_data->p_pos.y * 64, 0XFF0000);
	while (i < 5000)
	{
		radiant = 2 * M_PI * i / 5000;
		h = map_data->p_pos.x + r * cos(radiant);
		k = map_data->p_pos.y + r * sin(radiant);
		mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, h * 64, k * 64, 0XFFFFFF);
		printf("point in : (%f, %f)\n", h, k);
		i++;
	}
	raycast(map_data, r, define_fov(map_data, r));
	return (1);
}
