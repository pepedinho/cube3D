/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:00:33 by itahri            #+#    #+#             */
/*   Updated: 2024/09/30 14:18:16 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cube3D.h"

int	trace_perimeter(t_map_data *map_data, int r)
{
	double	h;
	double	k;
	double	radiant;
	int		i;

	i = 0;
	while (i < 5000)
	{
		radiant = 2 * M_PI * i / 5000;
		h = 5 + r * cos(radiant);
		k = 5 + r * sin(radiant);
		mlx_pixel_put(map_data->mlx.init, map_data->mlx.window, h
			* CIRCLE_SCALE, k * CIRCLE_SCALE, 0XFFFFFF);
		i++;
	}
	render_map(map_data);
	return (1);
}

void	trace_trait(t_map_data *map_data, double to_x, double to_y, int color)
{
	t_vec	start;
	double	x_step;
	double	y_step;
	int		steps;
	int		i;

	start.x = 10.5;
	start.y = 10.5;
	steps = fmax(fabs(to_x - start.x), fabs(to_y - start.y)) * PRECISION;
	x_step = to_x * map_data->p_pos.dir_length;
	y_step = to_y * map_data->p_pos.dir_length;
	x_step /= steps;
	y_step /= steps;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(map_data->mlx.init, map_data->mlx.window, start.x
			* MAP_SCALE, start.y * MAP_SCALE, color);
		start.x += x_step;
		start.y += y_step;
		i++;
	}
}

void	put_elment(t_map_data *map_data, t_vecint draw, int cas)
{
	if (cas == 0)
	{
		mlx_put_image_to_window(map_data->mlx.init, map_data->mlx.window,
			map_data->mlx.dot.img, 10 * MAP_SCALE, 10 * MAP_SCALE);
		trace_trait(map_data, map_data->p_pos.direction.x,
			map_data->p_pos.direction.y, 0X0000FF);
		mlx_put_image_to_window(map_data->mlx.init, map_data->mlx.window,
			map_data->mlx.white.img, draw.x * MAP_SCALE, draw.y * MAP_SCALE);
	}
	else
	{
		mlx_put_image_to_window(map_data->mlx.init, map_data->mlx.window,
			map_data->mlx.blue.img, draw.x * MAP_SCALE, draw.y * MAP_SCALE);
	}
}

void	brain(t_map_data *map_data, t_vecint *p, t_vecint *base, t_vecint *draw)
{
	char	**map;

	map = map_data->map;
	if (base->x >= 0 && base->x <= ft_strlen(map[base->y]))
	{
		if ((base->x - p->x) * (base->x - p->x) + (base->y - p->y) * (base->y
				- p->y) <= RADIUS * RADIUS)
		{
			draw->x = 10 + (base->x - p->x);
			draw->y = 10 + (base->y - p->y);
			if (map[base->y][base->x] == '1')
				put_elment(map_data, *draw, 0);
			else if (map[base->y][base->x] == 'D')
				put_elment(map_data, *draw, 1);
		}
	}
}

void	render_map(t_map_data *map_data)
{
	char		**map;
	t_vecint	p;
	t_vecint	base;
	t_vecint	draw;

	p.y = map_data->p_pos.r_y;
	p.x = map_data->p_pos.r_x;
	base.y = p.y - RADIUS;
	map = map_data->map;
	while (base.y <= p.y + RADIUS)
	{
		if (base.y >= 0 && base.y < map_ylen(map))
		{
			base.x = p.x - RADIUS;
			while (base.x <= p.x + RADIUS)
			{
				brain(map_data, &p, &base, &draw);
				base.x++;
			}
		}
		base.y++;
	}
}
