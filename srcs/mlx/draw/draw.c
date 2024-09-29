/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 03:51:46 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 03:52:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	draw_single_pixel(t_map_data *data, int x, int y, char *gun_color)
{
	char	*img_color;

	if (x >= 0 && x < data->mlx.width && y >= 0 && y < data->mlx.height)
	{
		img_color = (data->mlx.img.adrr + y
				* data->mlx.img.size_line + x
				* (data->mlx.img.bits_per_pixel_div8));
		*(unsigned int *)img_color = *(unsigned int *)gun_color;
	}
}

void	draw_scaled_pixel(t_map_data *data, t_vecint img, t_vecint gun,
	t_img *img_sprite)
{
	int			scale;
	t_vecint	img_scale;
	char		*gun_color;

	scale = 3;
	gun_color = img_sprite->adrr + (gun.y * img_sprite->size_line + gun.x
			* (img_sprite->bits_per_pixel_div8));
	if (*(unsigned int *)gun_color != TRANSPARENT)
	{
		img_scale.y = 0;
		while (img_scale.y < scale)
		{
			img_scale.x = 0;
			while (img_scale.x < scale)
			{
				int x = img.x + img_scale.x;
				int y = img.y + img_scale.y;
				draw_single_pixel(data, x, y, gun_color);
				img_scale.x++;
			}
			img_scale.y++;
		}
	}
}