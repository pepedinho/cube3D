/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:05:59 by itahri            #+#    #+#             */
/*   Updated: 2024/09/08 12:21:22 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	right_fov(t_map_data *data, double old_dir_x, double rot_speed,
		double old_plane_x)
{
	old_dir_x = data->p_pos.dir_x;
	data->p_pos.dir_x = data->p_pos.dir_x * cos(rot_speed) - data->p_pos.dir_y
		* sin(rot_speed);
	data->p_pos.dir_y = old_dir_x * sin(rot_speed) + data->p_pos.dir_y
		* cos(rot_speed);
	old_plane_x = data->p_pos.plane_x;
	data->p_pos.plane_x = data->p_pos.plane_x * cos(rot_speed)
		- data->p_pos.plane_y * sin(rot_speed);
	data->p_pos.plane_y = old_plane_x * sin(rot_speed) + data->p_pos.plane_y
		* cos(rot_speed);
}

void	left_fov(t_map_data *data, double old_dir_x, double rot_speed,
		double old_plane_x)
{
	old_dir_x = data->p_pos.dir_x;
	data->p_pos.dir_x = data->p_pos.dir_x * cos(-rot_speed) - data->p_pos.dir_y
		* sin(-rot_speed);
	data->p_pos.dir_y = old_dir_x * sin(-rot_speed) + data->p_pos.dir_y
		* cos(-rot_speed);
	old_plane_x = data->p_pos.plane_x;
	data->p_pos.plane_x = data->p_pos.plane_x * cos(-rot_speed)
		- data->p_pos.plane_y * sin(-rot_speed);
	data->p_pos.plane_y = old_plane_x * sin(-rot_speed) + data->p_pos.plane_y
		* cos(-rot_speed);
}
