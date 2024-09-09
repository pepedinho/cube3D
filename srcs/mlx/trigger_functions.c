/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:30:52 by itahri            #+#    #+#             */
/*   Updated: 2024/09/08 20:20:29 by madamou          ###   ########.fr       */
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
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = 0;
	old_plane_x = 0;
	if (keysym == XK_Escape)
		destroy_mlx(data);
	if (keysym == XK_Right)
		right_fov(data, old_dir_x, ROT_SPEED, old_plane_x);
	else if (keysym == XK_Left)
		left_fov(data, old_dir_x, ROT_SPEED, old_plane_x);
	else if (keysym == XK_w || keysym == XK_z)
		forward(data, MOVE_SPEED);
	else if (keysym == XK_s)
		behind(data, MOVE_SPEED);
	else if (keysym == XK_d)
		right(data, MOVE_SPEED);
	else if (keysym == XK_q || keysym == XK_a)
		left(data, MOVE_SPEED);
	else if (keysym == XK_space)
	{
		if (data->door_trigger)
		{
			data->map[data->door_y][data->door_x] = '0';
			data->door_trigger = 0;
		}
	}
	return (1);
}

int	render(t_map_data *data)
{
	static time_t	last_time;
	struct timeval	current_time;
	static size_t	frame_count;
	static size_t	fps;
	char			*str;
	int				x;
	int				y;
	int				rest;
	float			rot_speed;

	mlx_mouse_get_pos(data->mlx.init, data->mlx.window, &x, &y);
	rest = (data->mlx.width / 2) - x;
	rot_speed = ROT_SPEED * SENSITIVITY * abs(rest);
	if (abs(rest) > MIN_MOUSE_MOVE)
	{
		if (rest > 0)
			left_fov(data, 0, rot_speed, 0);
		if (rest < 0)
			right_fov(data, 0, rot_speed, 0);
		mlx_mouse_move(data->mlx.init, data->mlx.window, data->mlx.width / 2,
			data->mlx.height / 2);
	}
	if (data->mlx.window != NULL)
	{
		raycasting(data);
		mlx_put_image_to_window(data->mlx.init, data->mlx.window,
			data->mlx.img.img, 0, 0);
		gettimeofday(&current_time, NULL);
		if (current_time.tv_sec > last_time)
		{
			fps = frame_count;
			frame_count = 0;
			last_time = current_time.tv_sec;
		}
		str = ft_sprintf("fps = %d", fps);
		if (!str)
			destroy_mlx(data);
		mlx_string_put(data->mlx.init, data->mlx.window, 1800, 50, 0XFFFFFF,
			str);
		if (data->door_trigger)
			mlx_string_put(data->mlx.init, data->mlx.window, 900, 900, 0XFFFFF,
				"press space to open the door");
		free(str);
	}
	frame_count++;
	return (1);
}
