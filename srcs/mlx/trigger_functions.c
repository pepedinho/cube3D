/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 12:30:52 by itahri            #+#    #+#             */
/*   Updated: 2024/09/18 23:35:56 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3D.h"
#include "minilibx.h"
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
		right_fov(data, ROT_SPEED);
	if (data->key.cam_left == true)
		left_fov(data, ROT_SPEED);
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
	mlx_string_put(data->mlx.init, data->mlx.window, 1800, 50, WHITE, str);
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

void	display_gun(t_map_data *data, t_img img_sprite)
{
	int				center_x;
	int				center_y;
	char			*gun_color;
	char			*img_color;
	t_vecint		gun;
	t_vecint		img;
	int				scale;
	t_vecint		img_scale;

	scale = 3;
	gun.y = 0;
	center_x = data->mlx.width_div2;
	center_y = data->mlx.height_div2;
	while (gun.y < img_sprite.height)
	{
		gun.x = 0;
		while (gun.x < img_sprite.width)
		{
			gun_color = img_sprite.adrr + (gun.y * img_sprite.size_line + gun.x
					* (data->mlx.gun.bits_per_pixel / 8));
			if (*(unsigned int *)gun_color != TRANSPARENT)
			{
				img_scale.y = 0;
				while (img_scale.y < scale)
				{
					img_scale.x = 0;
					while (img_scale.x < scale)
					{
						img.x = center_x + gun.x * scale + img_scale.x;
						img.y = center_y + gun.y * scale + img_scale.y;
						if (img.x >= 0 && img.x < data->mlx.width && img.y >= 0
							&& img.y < data->mlx.height)
						{
							img_color = (data->mlx.img.adrr + img.y
									* data->mlx.img.size_line + img.x
									* (data->mlx.img.bits_per_pixel / 8));
							*(unsigned int *)img_color = *(unsigned int *)gun_color;
						}
						img_scale.x++;
					}
					img_scale.y++;
				}
			}
			gun.x++;
		}
		gun.y++;
	}
}

void	draw_crosshair_x(t_map_data *data, int center_x, int center_y, int size)
{
	int		x;
	char	*target;

	x = center_x - size;
	while (x <= center_x + size)
	{
		if (x >= 0 && x < data->mlx.width
			&& (x < center_x - 3 || x > center_x + 3))
		{
			target = data->mlx.img.adrr + (center_y
					* data->mlx.img.size_line + x
					* (data->mlx.img.bits_per_pixel / 8));
			*(unsigned int *)target = WHITE;
		}
		x++;
	}
}

void	draw_crosshair_y(t_map_data *data, int center_x, int center_y, int size)
{
	int		y;
	char	*target;

	y = center_y - size;
	while (y <= center_y + size)
	{
		if (y >= 0 && y < data->mlx.height
			&& (y < center_y - 3 || y > center_y + 3))
		{
			target = data->mlx.img.adrr + (y * data->mlx.img.size_line
					+ center_x * (data->mlx.img.bits_per_pixel / 8));
			*(unsigned int *)target = WHITE;
		}
		y++;
	}
}

void	display_crosshair(t_map_data *data)
{
	int	center_x;
	int	center_y;
	int	size;

	center_x = data->mlx.width / 2;
	center_y = data->mlx.height / 2;
	size = 10;
	draw_crosshair_x(data, center_x, center_y, size);
	draw_crosshair_y(data, center_x, center_y, size);
}


void	animate_gun(t_map_data *data, int *an)
{
	if (*an <= 5)
	{
		display_gun(data, data->mlx.shoot[0]);
		// usleep(100000);
	}
	else if (*an > 5 && *an <= 10)
	{
		display_gun(data, data->mlx.shoot[1]);
		// usleep(100000);
	}
	else if (*an > 15)
	{
		display_gun(data, data->mlx.gun);
		// usleep(100000);
	}
	mlx_put_image_to_window(data->mlx.init, data->mlx.window,
		data->mlx.img.img, 0, 0);
	++(*an);
	if (*an > 20)
		*an = 0;
}

int	is_valid_movement(t_map_data *data, double new_x, double new_y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)new_x;
	tile_y = (int)new_y;
	if (ft_is_in_charset(data->map[tile_y][tile_x], "1D"))
		return (0);
	return (1);
}

void	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
	if (length != 0)
	{
		*x /= length;
		*y /= length;
	}
}

void	enemies_movement(t_map_data *data)
{
	t_vec	dir;
	t_vec	new;
	double	speed;
	t_sprite *current;

	speed = 0.05;
	current = data->sprites;
	while (current)
	{
		if (current->type == MONSTER)
		{
			dir.x = data->p_pos.r_x - current->pos.x;
			dir.y = data->p_pos.r_y - current->pos.y;
			normalize_vector(&dir.x, &dir.y);
			new.x = current->pos.x + dir.x * speed;
			new.y = current->pos.y + dir.y * speed;
			if (is_valid_movement(data, new.x, new.y))
			{
				current->pos.x = new.x;
				current->pos.y = new.y;
			}
		}
		current = current->next;
	}
}

int	render(t_map_data *data)
{
	static time_t		last_time;
	struct timeval		current_time;
	static size_t		frame_count;
	static size_t		fps;
	static long long	frame_enemies;
	static int			cnt;

	mouse_movement(data);
	change_player(data);
	enemies_movement(data);
	if (data->mlx.window != NULL)
	{
		ft_memset(data->mlx.img.adrr, 0, (data->mlx.height
				* data->mlx.img.size_line + data->mlx.width
				* (data->mlx.img.bits_per_pixel / 8)));
		data->door_trigger = 0;
		raycasting(data);
		display_gun(data, data->mlx.gun);
		if (!cnt && check_if_crosshair_on_enemy(data))
			cnt++;
		if (cnt)
			animate_gun(data, &cnt);
		display_crosshair(data);
		mlx_put_image_to_window(data->mlx.init, data->mlx.window,
			data->mlx.img.img, 0, 0);
		gettimeofday(&current_time, NULL);
		if (current_time.tv_sec > last_time)
		{
			fps = frame_count;
			frame_count = 0;
			last_time = current_time.tv_sec;
			frame_enemies++;
			if (frame_enemies >= data->mlx.enemy.spawn)
			{
				frame_enemies = 0;
				// if (data->mlx.enemy.spawn != 0)
				// 	data->mlx.enemy.spawn--;
				random_enemies(data);
			}
		}
		string_put(data, fps);
		trace_perimeter(data, 5);
	}
	frame_count++;
	return (1);
}
