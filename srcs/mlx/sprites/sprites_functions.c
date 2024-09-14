/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 20:52:28 by madamou           #+#    #+#             */
/*   Updated: 2024/09/14 21:00:33 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"
#include <X11/X.h>

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

void	random_enemies(t_map_data *data)
{
	int		map_height;
	double	x;
	double	y;
	t_sprite *new;

	map_height = get_map_height(data->map);
	x = 0;
	y = 0;
	while (data->map[(int)floor(y)][(int)floor(x)] != '0')
	{
		y = rand_value(0, map_height);
		x = rand_value(0, ft_strlen(data->map[(int)floor(y)]));
	}
	// data->map[(int)floor(y)][(int)floor(x)] = 'M';
	new = new_sprite(x, y, MONSTER); // add protection because malloc
	add_back_sprite(&data->sprites, new);
}
