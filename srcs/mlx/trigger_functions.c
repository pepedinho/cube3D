/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:30:52 by itahri            #+#    #+#             */
/*   Updated: 2024/09/08 12:30:52 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

int	click_cross(t_map_data *data)
{
	destroy_mlx(data);
	return (1);
}

int	handle_input(int keysym, t_map_data *data)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;
	double	move_speed;

	move_speed = 0.1;
	rot_speed = 0.05;
	old_dir_x = 0;
	old_plane_x = 0;
	if (keysym == XK_Escape)
		destroy_mlx(data);
	if (keysym == XK_Right)
		right_fov(data, old_dir_x, rot_speed, old_plane_x);
	else if (keysym == XK_Left)
		left_fov(data, old_dir_x, rot_speed, old_plane_x);
	else if (keysym == XK_w || keysym == XK_z)
		forward(data, move_speed);
	else if (keysym == XK_s)
		behind(data, move_speed);
	else if (keysym == XK_d)
		right(data, move_speed);
	else if (keysym == XK_q || keysym == XK_a)
		left(data, move_speed);
	return (1);
}

int	render(t_map_data *data)
{
	static int	i;

	if (data->mlx.window != NULL && i++ % 240 == 0)
	{
		raycasting(data);
		i = 0;
	}
	return (0);
}
