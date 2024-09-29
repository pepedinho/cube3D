/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:31:31 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 03:48:01 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	mouse_movement(t_map_data *data)
{
	int		x;
	int		y;
	int		rest;
	float	rot_speed;

	mlx_mouse_get_pos(data->mlx.init, data->mlx.window, &x, &y);
	rest = data->mlx.width_div2 - x;
	rot_speed = ROT_SPEED * SENSITIVITY * abs(rest);
	if (abs(rest) > MIN_MOUSE_MOVE)
	{
		if (rest > 0)
			left_fov(data, rot_speed);
		if (rest < 0)
			right_fov(data, rot_speed);
		mlx_mouse_move(data->mlx.init, data->mlx.window, data->mlx.width_div2,
			data->mlx.height_div2);
	}
}

int	mouse_click(int button, int x, int y, t_map_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->key.fire = true;
	return (1);
}

void	handle_camera_movement(t_map_data *data)
{
	if (data->key.cam_right == true)
		right_fov(data, ROT_SPEED);
	if (data->key.cam_left == true)
		left_fov(data, ROT_SPEED);
}

void	handle_player_movement(t_map_data *data)
{
	if (data->key.up == true)
		forward(data, MOVE_SPEED + data->key.speed_boost);
	if (data->key.down == true)
		behind(data, MOVE_SPEED + data->key.speed_boost);
	if (data->key.right == true)
		right(data, MOVE_SPEED + data->key.speed_boost);
	if (data->key.left == true)
		left(data, MOVE_SPEED + data->key.speed_boost);
}

void	handle_door_interaction(t_map_data *data, bool *is_press)
{
	if (data->key.space == false)
		*is_press = false;
	if (data->key.space == true && data->door_trigger && *is_press == false)
	{
		if (data->map[data->door_y][data->door_x] == 'D')
			data->map[data->door_y][data->door_x] = 'O';
		else if (data->map[data->door_y][data->door_x] == 'O')
			data->map[data->door_y][data->door_x] = 'D';
		data->door_trigger = 0;
		*is_press = true;
	}
}
