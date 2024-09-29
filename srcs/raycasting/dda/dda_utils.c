/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:46:21 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 04:47:48 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	open_door_gesture(t_ray *ray, t_map_data *data)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perpwalldist = (ray->side_dist.y - ray->delta_dist.y);
	if (data->map[ray->map.y][ray->map.x] == 'O' && ray->perpwalldist <= 2)
	{
		data->door_trigger = 1;
		data->door_x = ray->map.x;
		data->door_y = ray->map.y;
	}
}
