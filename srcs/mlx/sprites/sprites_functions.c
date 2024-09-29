/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:52:28 by madamou           #+#    #+#             */
/*   Updated: 2024/09/28 23:49:33 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"
#include <X11/X.h>
#include <math.h>

int len_sprites(t_sprite *sprites)
{
	int i;

	i = 0;
	while (sprites)
	{
		sprites = sprites->next;
		++i;
	}
	return (i);
}

void add_back_sprite(t_sprite **sprites, t_sprite *add)
{
	t_sprite *buff;

	if (!*sprites)
		*sprites = add;	
	else
	{
		buff = *sprites;
		while (buff->next)
			buff = buff->next;
		buff->next = add;
	}
	add->next = NULL;
}

void del_one_sprite(t_sprite **sprites, t_sprite *to_del)
{
	t_sprite *current;
	t_sprite *before;

	before = NULL;
	current = *sprites;
	while (current && current != to_del)
	{
		before = current;
		current = current->next;
	}
	if (before)
		before->next = current->next;
	else
		*sprites = current->next;
	free(to_del);
}

void free_all_sprite(t_sprite *sprite)
{
	t_sprite *next;
	
	if (!sprite)
		return;
	next = sprite->next;
	free(sprite);
	free_all_sprite(next);
}

t_sprite *new_sprite(double x, double y, t_sprite_type type)
{
	t_sprite *new;

	new = malloc(sizeof(t_sprite));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->type = type;
	new->pos.x = x;
	new->pos.y = y;
	return (new);
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
	int		i;
	int		j;
	int		map_width;
	int		map_height;

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

void	random_enemies(t_map_data *data)
{
	int		map_height;
	double	x;
	double	y;
	t_sprite	*new;
	double	margin;

	map_height = get_map_height(data->map);
	margin = 1;
	x = 0;
	y = 0;
	while (!ft_is_in_charset(data->map[(int)floor(y)][(int)floor(x)], "0O")|| is_near_wall_or_door(data, x, y, margin))
	{
		y = rand_value(0, map_height);
		x = rand_value(0, ft_strlen(data->map[(int)floor(y)]));
	}
	new = new_sprite(x, y, MONSTER); // Protection pour malloc
	if (!new)
		return ;
	add_back_sprite(&data->sprites, new);
	data->nb_sprites = len_sprites(data->sprites);
}


