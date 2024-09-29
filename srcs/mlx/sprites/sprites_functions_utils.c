/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_functions_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:56:31 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 05:36:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

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
	t_vec		dir;
	t_vec		new;
	double		speed;
	t_sprite	*current;

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

void	sort_sprites(int *order, double *dist, int amount)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	while (i < amount - 1)
	{
		max = i;
		j = i + 1;
		while (j < amount)
		{
			if (dist[j] > dist[max])
				max = j;
			++j;
		}
		swap(&order[i], &order[max]);
		swap_double(&dist[i], &dist[max]);
		++i;
	}
}

int	is_near_wall_or_door(t_map_data *data, double x, double y, double margin)
{
	int	i;
	int	j;
	int	map_width;
	int	map_height;

	map_height = get_map_height(data->map);
	i = 0;
	while (i < map_height)
	{
		map_width = ft_strlen(data->map[i]);
		j = 0;
		while (j < map_width)
		{
			if (ft_is_in_charset(data->map[i][j], "1D"))
			{
				if (distance_euclid(x, y, (double)j, (double)i) < margin)
					return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}
