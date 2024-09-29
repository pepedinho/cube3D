/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:23:33 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 03:51:32 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	draw_gun(t_map_data *data, t_img img_sprite, t_vecint center, int scale)
{
	t_vecint	gun;
	t_vecint	img;

	gun.y = 0;
	while (gun.y < img_sprite.height)
	{
		gun.x = 0;
		while (gun.x < img_sprite.width)
		{
			img.x = center.x + gun.x * scale;
			img.y = center.y + gun.y * scale;
			draw_scaled_pixel(data, img, gun, &img_sprite);
			gun.x++;
		}
		gun.y++;
	}
}

void	display_gun(t_map_data *data, t_img img_sprite)
{
	t_vecint center;
	int	scale;

	center.x = data->mlx.width_div2;
	center.y = data->mlx.height_div2;
	scale = 3;
	draw_gun(data, img_sprite, center, scale);
}

void	animate_gun(t_map_data *data, int *an)
{
	if (*an <= 5)
		display_gun(data, data->mlx.shoot[0]);
	else if (*an > 5 && *an <= 10)
		display_gun(data, data->mlx.shoot[1]);
	else if (*an > 15)
		display_gun(data, data->mlx.gun);
	mlx_put_image_to_window(data->mlx.init, data->mlx.window,
		data->mlx.img.img, 0, 0);
	++(*an);
	if (*an > 20)
	{
		*an = 0;
		data->key.fire = false;
	}
}

void	handle_gun_fire(t_map_data *data, int *cnt)
{
	if (data->key.fire == true)
	{
		if (!*cnt)
			check_if_crosshair_on_enemy(data);
		animate_gun(data, cnt);
	}
}
