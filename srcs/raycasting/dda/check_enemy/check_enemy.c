/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:56:35 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 05:45:23 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/cube3D.h"

int	is_enemy_visible(t_map_data *data, double enemy_x, double enemy_y)
{
	t_vec		player;
	t_vec		dir;
	double		distance;
	t_vec		current;
	t_vecint	map;

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

t_vec	normalize_vector_enemy(double x, double y)
{
	t_vec	normalized;
	double	inv_norm;

	inv_norm = 1.0 / sqrt(x * x + y * y);
	normalized.x = x * inv_norm;
	normalized.y = y * inv_norm;
	return (normalized);
}

double	calculate_distance(t_map_data *data, double enemy_x, double enemy_y)
{
	double	dx;
	double	dy;

	dx = enemy_x - data->p_pos.r_x;
	dy = enemy_y - data->p_pos.r_y;
	return (sqrt(dx * dx + dy * dy));
}

int	is_looking_at_enemy(t_map_data *data, double enemy_x, double enemy_y,
	double base_tolerance)
{
	t_vec	camera_dir;
	t_vec	enemy_dir;
	double	distance;
	double	dynamic_tolerance;
	double	dot_product;

	camera_dir = normalize_vector_enemy(data->p_pos.dir_x, data->p_pos.dir_y);
	distance = calculate_distance(data, enemy_x, enemy_y);
	enemy_dir = normalize_vector_enemy(enemy_x - data->p_pos.r_x,
			enemy_y - data->p_pos.r_y);
	dynamic_tolerance = base_tolerance + (1.0 / distance);
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
