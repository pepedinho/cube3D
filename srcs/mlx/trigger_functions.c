/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:30:52 by itahri            #+#    #+#             */
/*   Updated: 2024/09/14 00:31:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"
#include <X11/X.h>

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
	if (data->key.cam_right == true)
		right_fov(data, 0, ROT_SPEED, 0);
	if (data->key.cam_left == true)
		left_fov(data, 0, ROT_SPEED, 0);
	if (data->key.up == true)
		forward(data, MOVE_SPEED + data->key.speed_boost);
	if (data->key.down == true)
		behind(data, MOVE_SPEED + data->key.speed_boost);
	if (data->key.right == true)
		right(data, MOVE_SPEED + data->key.speed_boost);
	if (data->key.left == true)
		left(data, MOVE_SPEED + data->key.speed_boost);
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

double	rand_value(double min, double max)
{
	double	range;
	double	div;

	range = (max - min);
	div = RAND_MAX / range;
	return (min + (rand() / div));
}

int	get_map_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

void	random_enemies(t_map_data *data)
{
	int		map_height;
	double	x;
	double	y;

	map_height = get_map_height(data->map);
	x = 0;
	y = 0;
	while (data->map[(int)floor(y)][(int)floor(x)] != '0')
	{
		y = rand_value(0, map_height);
		x = rand_value(0, ft_strlen(data->map[(int)floor(y)]));
	}
	data->map[(int)floor(y)][(int)floor(x)] = 'M';
}

int	render(t_map_data *data)
{
	static time_t	last_time;
	struct timeval	current_time;
	static size_t	frame_count;
	static size_t	fps;

	// static long long frame_enemies;
	gettimeofday(&current_time, NULL);
	if (last_time != 0)
	{
		data->delta_time = (current_time.tv_sec - last_time)
			+ ((current_time.tv_usec - last_time) / 1000000.0);
	}
	last_time = current_time.tv_sec;
	mouse_movement(data);
	change_player(data);
	if (data->mlx.window != NULL)
	{
		ft_memset(data->mlx.img.adrr, 0, (data->mlx.height
				* data->mlx.img.size_line + data->mlx.width
				* (data->mlx.img.bits_per_pixel / 8)));
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
			// frame_enemies++;
			// if (frame_enemies >= data->mlx.enemy.spawn)
			// {
			// 	frame_enemies = 0;
			// 	if (data->mlx.enemy.spawn != 0)
			// 		data->mlx.enemy.spawn--;
			// 	random_enemies(data);
			// }
		}
		string_put(data, fps);
		trace_perimeter(data, 5);
	}
	frame_count++;
	return (1);
}
