/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:25:58 by itahri            #+#    #+#             */
/*   Updated: 2024/09/14 00:36:46 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	right(t_map_data *data, double move_speed)
{
	if (data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
			+ data->p_pos.plane_x * move_speed)] != '1'
		&& data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
			+ data->p_pos.plane_x * move_speed)] != 'D')
		data->p_pos.r_x += data->p_pos.plane_x * move_speed;
	if (data->map[(int)(data->p_pos.r_y + data->p_pos.plane_y
			* move_speed)][(int)(data->p_pos.r_x)] != '1'
		&& data->map[(int)(data->p_pos.r_y + data->p_pos.plane_y
			* move_speed)][(int)(data->p_pos.r_x)] != 'D')
		data->p_pos.r_y += data->p_pos.plane_y * move_speed;
}

void	left(t_map_data *data, double move_speed)
{
	if (data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
			- data->p_pos.plane_x * move_speed)] != '1'
		&& data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
			- data->p_pos.plane_x * move_speed)] != 'D')
		data->p_pos.r_x -= data->p_pos.plane_x * move_speed;
	if (data->map[(int)(data->p_pos.r_y - data->p_pos.plane_y
			* move_speed)][(int)(data->p_pos.r_x)] != '1'
		&& data->map[(int)(data->p_pos.r_y - data->p_pos.plane_y
			* move_speed)][(int)(data->p_pos.r_x)] != 'D')
		data->p_pos.r_y -= data->p_pos.plane_y * move_speed;
}

void forward(t_map_data *data, double move_speed)
{
    if (data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
		+ data->p_pos.dir_x * move_speed)] != '1'
        && data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
		+ data->p_pos.dir_x * move_speed)] != 'D')
        data->p_pos.r_x += data->p_pos.dir_x * move_speed;
    if (data->map[(int)(data->p_pos.r_y + data->p_pos.dir_y
		* move_speed)][(int)(data->p_pos.r_x)] != '1'
        && data->map[(int)(data->p_pos.r_y + data->p_pos.dir_y
		* move_speed)][(int)(data->p_pos.r_x)] != 'D')
        data->p_pos.r_y += data->p_pos.dir_y * move_speed;
}


void	behind(t_map_data *data, double move_speed)
{
	if (data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
			- data->p_pos.dir_x * move_speed)] != '1'
		&& data->map[(int)(data->p_pos.r_y)][(int)(data->p_pos.r_x
			- data->p_pos.dir_x * move_speed)] != 'D')
		data->p_pos.r_x -= data->p_pos.dir_x * move_speed;
	if (data->map[(int)(data->p_pos.r_y - data->p_pos.dir_y
			* move_speed)][(int)(data->p_pos.r_x)] != '1'
		&& data->map[(int)(data->p_pos.r_y - data->p_pos.dir_y
			* move_speed)][(int)(data->p_pos.r_x)] != 'D')
		data->p_pos.r_y -= data->p_pos.dir_y * move_speed;
}
