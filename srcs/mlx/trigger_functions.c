/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:30:52 by itahri            #+#    #+#             */
/*   Updated: 2024/09/11 20:02:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"

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
	return (1);
}

void	change_player(t_map_data *data)
{
	static bool	is_press;

	if (data->key.escape == true)
		destroy_mlx(data);
	if (data->key.cam_right == true)
		right_fov(data, 0, ROT_SPEED, 0);
	if (data->key.cam_left == true)
		left_fov(data, 0, ROT_SPEED, 0);
	if (data->key.up == true)
		forward(data, MOVE_SPEED);
	if (data->key.down == true)
		behind(data, MOVE_SPEED);
	if (data->key.right == true)
		right(data, MOVE_SPEED);
	if (data->key.left == true)
		left(data, MOVE_SPEED);
	if (data->key.space == false)
		is_press = false;
	if (data->key.space == true)
	{
		if (data->door_trigger && is_press == false)
		{
			if (data->map[data->door_y][data->door_x] == 'D')
				data->map[data->door_y][data->door_x] = 'O';
			else if (data->map[data->door_y][data->door_x] == 'O')
				data->map[data->door_y][data->door_x] = 'D';
			data->door_trigger = 0;
			is_press = true;
		}
	}
}

void	string_put(t_map_data *data, size_t fps)
{
	char	*str;

	str = ft_sprintf("fps = %d", fps);
	if (!str)
		destroy_mlx(data);
	mlx_string_put(data->mlx.init, data->mlx.window, 1800, 50, 0XFFFFFF, str);
	if (data->door_trigger && data->map[data->door_y][data->door_x] == 'D')
		mlx_string_put(data->mlx.init, data->mlx.window, 900, 900, 0XFFFFF,
			"press space to open the door");
	else if (data->door_trigger && data->map[data->door_y][data->door_x] == 'O')
		mlx_string_put(data->mlx.init, data->mlx.window, 900, 900, 0XFFFFF,
			"press space to close the door");
	free(str);
}

void	mouse_movement(t_map_data *data)
{
	int		x;
	int		y;
	int		rest;
	float	rot_speed;

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
}

int	render(t_map_data *data)
{
	static time_t	last_time;
	struct timeval	current_time;
	static size_t	frame_count;
	static size_t	fps;

	mouse_movement(data);
	change_player(data);
	if (data->mlx.window != NULL)
	{
		data->door_trigger = 0;
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
		string_put(data, fps);
		trace_perimeter(data, 5);
	}
	frame_count++;
	return (1);
}
