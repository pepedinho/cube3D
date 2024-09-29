/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:51:44 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 05:46:22 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/cube3D.h"

t_vec	set_current_sprite_position(t_map_data *data, int index)
{
	t_vec		sprite;
	int			i;
	t_sprite	*current_sprite;

	i = 0;
	current_sprite = data->sprites;
	while (i++ < index)
		current_sprite = current_sprite->next;
	sprite.x = current_sprite->pos.x - data->p_pos.r_x;
	sprite.y = current_sprite->pos.y - data->p_pos.r_y;
	return (sprite);
}

t_vec	set_transform(t_map_data *data, t_vec sprite)
{
	t_vec	transform;
	double	inv_det;

	inv_det = 1.0 / (data->p_pos.plane_x * data->p_pos.dir_y - data->p_pos.dir_x
			* data->p_pos.plane_y);
	transform.x = inv_det * (data->p_pos.dir_y * sprite.x - data->p_pos.dir_x
			* sprite.y);
	transform.y = inv_det * (-data->p_pos.plane_y * sprite.x
			+ data->p_pos.plane_x * sprite.y);
	return (transform);
}
