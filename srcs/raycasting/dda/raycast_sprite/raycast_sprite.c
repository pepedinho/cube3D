/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 04:48:47 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 05:47:11 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/cube3D.h"

int	*order_sprite_with_distance(t_map_data *data)
{
	int			*sprite_order;
	double		*sprite_distance;
	int			i;
	t_sprite	*current;

	sprite_order = malloc(sizeof(int) * data->nb_sprites);
	if (!sprite_order)
		destroy_mlx(data);
	sprite_distance = malloc(sizeof(double) * data->nb_sprites);
	if (!sprite_distance)
		(free(sprite_order), destroy_mlx(data));
	i = 0;
	current = data->sprites;
	while (i < data->nb_sprites)
	{
		sprite_order[i] = i;
		sprite_distance[i] = (data->p_pos.r_x - current->pos.x)
			* (data->p_pos.r_x - current->pos.x) + (data->p_pos.r_y
				- current->pos.y) * (data->p_pos.r_y - current->pos.y);
		++i;
		current = current->next;
	}
	sort_sprites(sprite_order, sprite_distance, data->nb_sprites);
	free(sprite_distance);
	return (sprite_order);
}

void	set_draw_start_end_sprite(t_map_data *data, t_render_sprite *render_s)
{
	render_s->draw_start.y = -render_s->sprite_height / 2
		+ data->mlx.height_div2;
	if (render_s->draw_start.y < 0)
		render_s->draw_start.y = 0;
	render_s->draw_end.y = render_s->sprite_height / 2 + data->mlx.height_div2;
	if (render_s->draw_end.y >= data->mlx.height)
		render_s->draw_end.y = data->mlx.height - 1;
	render_s->draw_start.x = -render_s->sprite_width / 2
		+ render_s->sprite_screen_x;
	if (render_s->draw_start.x < 0)
		render_s->draw_start.x = 0;
	render_s->draw_end.x = render_s->sprite_width / 2
		+ render_s->sprite_screen_x;
	if (render_s->draw_end.x >= data->mlx.width)
		render_s->draw_end.x = data->mlx.width - 1;
}

void	set_sprite_data(t_map_data *data, int index, t_render_sprite *render_s)
{
	t_vec	sprite;

	sprite = set_current_sprite_position(data, index);
	render_s->transform = set_transform(data, sprite);
	render_s->sprite_screen_x = (int)(data->mlx.width_div2 * (1
				+ render_s->transform.x / render_s->transform.y));
	render_s->sprite_height = (int)fabs(data->mlx.height
			/ render_s->transform.y);
	render_s->sprite_width = (int)fabs(data->mlx.height
			/ render_s->transform.y);
	set_draw_start_end_sprite(data, render_s);
	render_s->x = render_s->draw_start.x;
}

void	draw_stripe_sprite(t_map_data *data, t_render_sprite *render_s,
		t_vecint *tex)
{
	render_s->y = render_s->draw_start.y;
	while (render_s->y < render_s->draw_end.y)
	{
		render_s->d = render_s->y * 256 - data->mlx.height * 128
			+ render_s->sprite_height * 128;
		tex->y = ((render_s->d * data->mlx.enemy.img.height)
				/ render_s->sprite_height) / 256;
		render_s->texture_color = data->mlx.enemy.img.adrr + (tex->y
				* data->mlx.enemy.img.size_line + tex->x
				* (data->mlx.enemy.img.bits_per_pixel_div8));
		render_s->screen_pixel = data->mlx.img.adrr + (render_s->y
				* data->mlx.img.size_line + render_s->x
				* (data->mlx.img.bits_per_pixel_div8));
		if (*(unsigned int *)render_s->texture_color != TRANSPARENT)
			*(unsigned int *)render_s->screen_pixel
				= *(unsigned int *)render_s->texture_color;
		render_s->y++;
	}
}

void	sprite_render(t_map_data *data, t_render_sprite *render_s, t_ray *ray)
{
	t_vecint	tex;

	while (render_s->x < render_s->draw_end.x)
	{
		tex.x = (int)(256 * (render_s->x - (-render_s->sprite_width / 2
						+ render_s->sprite_screen_x))
				* data->mlx.enemy.img.width / render_s->sprite_width) / 256;
		if (render_s->transform.y > 0 && render_s->x > 0
			&& render_s->x < data->mlx.width
			&& render_s->transform.y < ray->z_buffer[render_s->x])
			draw_stripe_sprite(data, render_s, &tex);
		render_s->x++;
	}
}
