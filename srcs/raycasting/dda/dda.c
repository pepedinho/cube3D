/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:44:57 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 04:45:53 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	handle_hit(t_ray *ray, t_map_data *data)
{
	if (data->map[ray->map.y][ray->map.x] == 'O')
		open_door_gesture(ray, data);
	if (data->map[ray->map.y][ray->map.x] == '1'
		|| data->map[ray->map.y][ray->map.x] == 'D')
		ray->hit = 1;
}

void	calculate_perpwalldist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perpwalldist = (ray->side_dist.y - ray->delta_dist.y);
}

void	update_player_direction(t_ray *ray, t_map_data *data)
{
	if (ray->camera_x == 0.0)
	{
		data->p_pos.direction.x = data->p_pos.dir_x;
		data->p_pos.direction.y = data->p_pos.dir_y;
		data->p_pos.dir_length = ray->perpwalldist;
	}
}

void	check_door_trigger(t_ray *ray, t_map_data *data)
{
	if (data->map[ray->map.y][ray->map.x] == 'D' && ray->perpwalldist <= 2)
	{
		data->door_trigger = 1;
		data->door_x = ray->map.x;
		data->door_y = ray->map.y;
	}
}

void	dda(t_ray *ray, t_map_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		handle_hit(ray, data);
	}
	calculate_perpwalldist(ray);
	update_player_direction(ray, data);
	check_door_trigger(ray, data);
}
