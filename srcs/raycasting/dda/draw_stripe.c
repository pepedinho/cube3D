/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stripe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 05:00:07 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 05:00:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

void	fill_ceiling(t_map_data *map)
{
	char	*target;
	int		i;
	int		end;

	i = 0;
	end = map->mlx.height_div2 * map->mlx.img.size_line + map->mlx.width
		* (map->mlx.img.bits_per_pixel_div8);
	while (i <= end)
	{
		target = map->mlx.img.adrr + i;
		if (*(unsigned int *)target != (unsigned int)map->input.ceiling_color)
			*(unsigned int *)target = (unsigned int)map->input.ceiling_color;
		i += (map->mlx.img.bits_per_pixel_div8);
	}
}

void	draw_wall_stripe(t_map_data *map, t_ray *ray, int i, t_vecint texture)
{
	char	*texture_color;
	char	*screen_pixel;
	double	step;
	double	tex_pos;

	step = 1.0 * map->mlx.wall[i].height / ray->wallheight;
	tex_pos = (ray->draw_start - map->mlx.height / 2 + ray->wallheight / 2)
		* step;
	while (ray->coord.y <= ray->draw_end)
	{
		texture.y = (int)tex_pos % map->mlx.wall[i].height;
		tex_pos += step;
		texture_color = map->mlx.wall[i].adrr + (texture.y
				* map->mlx.wall[i].size_line + texture.x
				* (map->mlx.wall[i].bits_per_pixel_div8));
		screen_pixel = map->mlx.img.adrr + (ray->coord.y
				* map->mlx.img.size_line + ray->coord.x
				* (map->mlx.img.bits_per_pixel_div8));
		if (*(unsigned int *)screen_pixel != *(unsigned int *)texture_color)
			*(unsigned int *)screen_pixel = *(unsigned int *)texture_color;
		ray->coord.y++;
	}
}

void	draw_door_stripe(t_map_data *map, t_ray *ray, t_vecint texture)
{
	char	*texture_color;
	char	*screen_pixel;
	double	step;
	double	tex_pos;

	step = 1.0 * map->mlx.door.height / ray->wallheight;
	tex_pos = (ray->draw_start - map->mlx.height / 2 + ray->wallheight / 2)
		* step;
	while (ray->coord.y <= ray->draw_end)
	{
		texture.y = (int)tex_pos % map->mlx.door.height;
		tex_pos += step;
		texture_color = map->mlx.door.adrr + (texture.y
				* map->mlx.door.size_line + texture.x
				* (map->mlx.door.bits_per_pixel_div8));
		screen_pixel = map->mlx.img.adrr + (ray->coord.y
				* map->mlx.img.size_line + ray->coord.x
				* (map->mlx.img.bits_per_pixel_div8));
		if (*(unsigned int *)screen_pixel != *(unsigned int *)texture_color)
			*(unsigned int *)screen_pixel = *(unsigned int *)texture_color;
		ray->coord.y++;
	}
}

void	fill_floor(t_map_data *map)
{
	char	*target;
	int		i;
	int		end;
	
	i = map->mlx.height_div2 * map->mlx.img.size_line + map->mlx.width
		* (map->mlx.img.bits_per_pixel_div8);
	end = map->mlx.height * map->mlx.img.size_line + map->mlx.width
		* (map->mlx.img.bits_per_pixel_div8);
	while (i <= end)
	{
		target = map->mlx.img.adrr + i;
		if (*(unsigned int *)target != (unsigned int)map->input.floor_color)
			*(unsigned int *)target = (unsigned int)map->input.floor_color;
		i += (map->mlx.img.bits_per_pixel_div8);
	}
}

void	print_stripe(t_map_data *map, t_ray *ray, int i)
{
	t_vecint texture;

	ray->coord.y = ray->draw_start;
	if (i == D)
	{
		texture.x = (int)(ray->wall_x * map->mlx.door.width);
		if ((ray->side == 0 && ray->ray_dir.x > 0) || (ray->side == 1
				&& ray->ray_dir.y < 0))
			texture.x = map->mlx.door.width - texture.x - 1;		
		draw_door_stripe(map, ray, texture);
	}
	else
	{
		texture.x = (int)(ray->wall_x * map->mlx.door.width);
		if ((ray->side == 0 && ray->ray_dir.x > 0) || (ray->side == 1
				&& ray->ray_dir.y < 0))
			texture.x = map->mlx.door.width - texture.x - 1;
		draw_wall_stripe(map, ray, i, texture);
	}
}
