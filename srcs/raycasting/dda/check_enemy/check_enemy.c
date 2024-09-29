/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_enemy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:56:35 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 04:56:59 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/cube3D.h"

int	is_enemy_visible(t_map_data *data, double enemy_x, double enemy_y)
{
	t_vec player;
	t_vec dir;
	double	distance;
	t_vec current;
	t_vecint map;

	player.x = data->p_pos.r_x;
	player.y = data->p_pos.r_y;
	distance = sqrt(pow(enemy_x - player.x, 2) + pow(enemy_y - player.y, 2));
	dir.x = (enemy_x - player.x) / distance;
	dir.y = (enemy_y - player.y) / distance;
	current.x = player.x;
	current.y = player.y;
	while (sqrt((current.x - player.x) * (current.x - player.x) + (current.y
				- player.y) * (current.y - player.y)) < distance)
	{
		current.x += dir.x * 0.1;
		current.y += dir.y * 0.1;
		map.x = (int)current.x;
		map.y = (int)current.y;
		if (data->map[map.y][map.x] == '1')
			return (0);
	}
	return (1);
}

int	is_looking_at_enemy(t_map_data *data, double enemy_x, double enemy_y,
		double base_tolerance)
{
	double	inv_norm_camera;
	t_vec camera_dir;
	t_vec enemy_dir;
	double	inv_norm_enemy;
	double	dot_product;
	double	distance;
	double	dynamic_tolerance;

	inv_norm_camera = 1.0 / sqrt(data->p_pos.dir_x * data->p_pos.dir_x
			+ data->p_pos.dir_y * data->p_pos.dir_y);
	camera_dir.x = data->p_pos.dir_x * inv_norm_camera;
	camera_dir.y = data->p_pos.dir_y * inv_norm_camera;
	enemy_dir.x = enemy_x - data->p_pos.r_x;
	enemy_dir.y = enemy_y - data->p_pos.r_y;
	distance = sqrt(enemy_dir.x * enemy_dir.x + enemy_dir.y * enemy_dir.y);
	inv_norm_enemy = 1.0 / distance;
	enemy_dir.x *= inv_norm_enemy;
	enemy_dir.y *= inv_norm_enemy;
	dynamic_tolerance = base_tolerance + (1.0 / distance); // try to change this for better precision on fire
	dot_product = camera_dir.x * enemy_dir.x + camera_dir.y * enemy_dir.y;
	if (dot_product > cos(dynamic_tolerance * M_PI / 180.0))
		if (is_enemy_visible(data, enemy_x, enemy_y))
			return (1);
	return (0);
}


int	check_if_crosshair_on_enemy(t_map_data *data)
{
	t_sprite	*current;

	current = data->sprites;
	while (current)
	{
		if (is_looking_at_enemy(data, current->pos.x, current->pos.y, 2) == 1)
		{
			del_one_sprite(&data->sprites, current);
			--data->nb_sprites;
			return (1);
		}
		current = current->next;
	}
	return (0);
}
