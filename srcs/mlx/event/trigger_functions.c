/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:30:52 by itahri            #+#    #+#             */
/*   Updated: 2024/09/29 03:47:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"
#include <X11/X.h>
#include <stdbool.h>

int	click_cross(t_map_data *data)
{
	destroy_mlx(data);
	return (1);
}

int	key_prees(int keysym, t_map_data *data)
{
	if (keysym == XK_Right)
		data->key.cam_right = true;
	if (keysym == XK_Left)
		data->key.cam_left = true;
	if (keysym == XK_w || keysym == XK_z || keysym == XK_Up)
		data->key.up = true;
	if (keysym == XK_s || keysym == XK_Down)
		data->key.down = true;
	if (keysym == XK_d)
		data->key.right = true;
	if (keysym == XK_q || keysym == XK_a)
		data->key.left = true;
	if (keysym == XK_Escape)
		data->key.escape = true;
	if (keysym == XK_space)
		data->key.space = true;
	if (keysym == XK_Shift_L)
		data->key.speed_boost = 0.07;
	return (1);
}

int	key_release(int keysym, t_map_data *data)
{
	if (keysym == XK_Right)
		data->key.cam_right = false;
	if (keysym == XK_Left)
		data->key.cam_left = false;
	if (keysym == XK_w || keysym == XK_z || keysym == XK_Up)
		data->key.up = false;
	if (keysym == XK_s || keysym == XK_Down)
		data->key.down = false;
	if (keysym == XK_d)
		data->key.right = false;
	if (keysym == XK_q || keysym == XK_a)
		data->key.left = false;
	if (keysym == XK_space)
		data->key.space = false;
	if (keysym == XK_Shift_L)
		data->key.speed_boost = 0.0;
	return (1);
}


void	change_player(t_map_data *data)
{
	static bool	is_press;

	if (data->key.escape == true)
		destroy_mlx(data);
	handle_camera_movement(data);
	handle_player_movement(data);
	handle_door_interaction(data, &is_press);
}

