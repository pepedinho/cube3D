/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/08 19:07:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycatsing.h"

#define PRECISION 50

// void	trace_trait(t_map_data *map_data, double to_x, double to_y, int color)
// {
// 	double	x_start;
// 	double	y_start;
// 	double	x_step;
// 	double	y_step;
// 	int		steps;
// 	int		i;

// 	x_start = map_data->p_pos.r_x;
// 	y_start = map_data->p_pos.r_y;
// 	steps = fmax(fabs(to_x - x_start), fabs(to_y - y_start)) * PRECISION;
// 	x_step = (to_x - x_start) / steps;
// 	y_step = (to_y - y_start) / steps;
// 	i = 0;
// 	while (i <= steps)
// 	{
// 		mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, x_start
// 			* WIDTH, y_start * HEIGHT, color);
// 		x_start += x_step;
// 		y_start += y_step;
// 		i++;
// 	}
// }

// void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1,
//	int color)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = (x0 < x1) ? 1 : -1;
// 	int sy = (y0 < y1) ? 1 : -1;
// 	int err = dx - dy;
// 	int e2;

// 	while (1)
// 	{
// 		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break ;
// 		e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// void trace_trait_v2(t_map_data *map_data, double angle, double len)
// {
// 	double	ray_dir_x;
// 	double	ray_dir_y;
// 	double	end_x;
// 	double	end_y;
// 	int		start_x;
// 	int		start_y;

// 	// Calculer la direction du rayon en fonction de l'angle
// 	ray_dir_x = cos(angle);
// 	ray_dir_y = sin(angle);

// 	// Position de départ (position du joueur)
// 	start_x = (int)(map_data->p_pos.r_x * WIDTH);
// Conversion en coordonnées écran
// 	start_y = (int)(map_data->p_pos.r_y * HEIGHT);

// 	// Calculer la position finale du trait (rayon)
// 	end_x = start_x + len * ray_dir_x;
// 	end_y = start_y + len * ray_dir_y;

// 	// Dessiner le trait depuis la position du joueur (start_x,
//		start_y) jusqu'à (end_x, end_y)
// 	draw_line(map_data->mlx->init, map_data->mlx->window, start_x, start_y,
//		(int)end_x, (int)end_y, 0xFF0000);
// }

// double	*define_fov(t_map_data *map_data, int r, double alpha)
// {
// 	double	radiant;
// 	double	x1;
// 	double	x2;
// 	double	y1;
// 	double	y2;
// 	double	*angles;

// 	angles = malloc(sizeof(double) * 2);
// 	radiant = 66 * M_PI / 180;
// 	x1 = map_data->p_pos.r_x + r * cos(alpha);
// 	y1 = map_data->p_pos.r_y + r * sin(alpha);
// 	x2 = map_data->p_pos.r_x + r * cos(alpha + radiant);
// 	y2 = map_data->p_pos.r_y + r * sin(alpha + radiant);
// 	// printf("fov1 ==  : (%f, %f)\n", x1, y1);
// 	// printf("fov2 ==  : (%f, %f)\n", x2, y2);
// 	trace_trait(map_data, x1, y1, 0XFFFF00);
// 	trace_trait(map_data, x2, y2, 0X008000);
// 	angles[0] = alpha;
// 	angles[1] = alpha + radiant;
// 	if (angles[1] > 2 * M_PI)
// 		angles[1] -= 2 * M_PI;
// 	return (angles);
// }

// int	dda(t_map_data *map_data, double angle)
// {
// 	double	ray_dir_x;
// 	double	ray_dir_y;
// 	int		map_x;
// 	int		map_y;
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	int		step_x;
// 	int		step_y;
// 	int		hit;
// 	double ray_length;

// 	ray_dir_x = cos(angle);
// 	ray_dir_y = sin(angle);
// 	// if (ray_dir_y < 0)
// 	// 	printf("ray_dix_x == %f || ray_dir_y == %f\n", ray_dir_x, ray_dir_y);
// 	// if (ray_dir_x < 0)
// 	// 	printf("ray_dix_x == %f || ray_dir_y == %f\n", ray_dir_x, ray_dir_y);
// 	map_x = floor(map_data->p_pos.r_x);
// 	map_y = floor(map_data->p_pos.r_y);
// 	hit = 0;
// 	if (ray_dir_x == 0)
// 		ray_dir_x = 1e-30;
// 	if (ray_dir_y == 0)
// 		ray_dir_y = 1e-30;
// 	delta_dist_x = fabs(1 / ray_dir_x);
// 	delta_dist_y = fabs(1 / ray_dir_y);
// 	step_x = sign(ray_dir_x);
// 	step_y = sign(ray_dir_y);
// 	side_dist_x = set_side_dist(ray_dir_x, map_data->p_pos.b_x, map_x,
//			delta_dist_x);
// 	side_dist_y = set_side_dist(ray_dir_y, map_data->p_pos.b_y, map_y,
//			delta_dist_y);
// 	while (hit == 0)
// 	{
//         // printf("\n\nmap_x: %d, map_y: %d, side_dist_x: %f, side_dist_y:
//	%f\n", map_x, map_y, side_dist_x, side_dist_y);
// 		// printf("actuel case == %c\n\n", map_data->map[map_y][map_x]);
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_dist_x;
// 			map_x += step_x;
// 		}
// 		else
// 		{
// 			side_dist_y += delta_dist_y;
// 			map_y += step_y;
// 		}
// 		if (map_data->map[map_y][map_x] == '1')
// 			hit = 1;
// 	}
// 	if (side_dist_x < side_dist_y)
// 		ray_length = side_dist_x - delta_dist_x;
// 	else
// 		ray_length = side_dist_y - delta_dist_y;
// 	printf("raylength == %f\n", ray_length);
// 	trace_trait_v2(map_data, angle, ray_length);
// 	// trace_trait(map_data, map_x, map_y, 0XFF0000);
// 	return (1);
// }

// int	raycast(t_map_data *map_data, int r, double *start_end, int num_rays)
// {
// 	double	increment;
// 	double	current_angle;
// 	int		i;

// 	(void)r;
// 	increment = (start_end[1] - start_end[0]) / num_rays;
// 	if (start_end[0] > start_end[1])
// 		increment = (2 * M_PI - start_end[0] + start_end[1]) / num_rays;
// 	i = 0;
// 	while (i < num_rays)
// 	{
// 		current_angle = start_end[0] + i * increment;
// 		if (current_angle >= 2 * M_PI)
// 			current_angle -= 2 * M_PI;
// 		printf("current angle == %f\n", current_angle);
// 		dda(map_data, current_angle);
// 		i++;
// 	}
// 	free(start_end);
// 	return (1);
// }

// int	find_r(t_map_data *map_data)
// {
// 	int	x;

// 	int	y;
// 	int	r;
// 	int	iterator;

// 	x = map_data->p_pos.b_x + 1;
// 	iterator = 1;
// 	while (map_data->map[map_data->p_pos.b_y][x] == '0')
// 	{
// 		x++;
// 		iterator++;
// 	}
// 	r = iterator;
// 	iterator = 0;
// 	y = map_data->p_pos.b_y + 1;
// 	while (map_data->map[y][map_data->p_pos.b_x] == '0')
// 	{
// 		y++;
// 		iterator++;
// 	}
// 	if (iterator > r)
// 		r = iterator;
// 	iterator = 0;
// 	x = map_data->p_pos.b_x - 1;
// 	while (x >= 0 && map_data->map[map_data->p_pos.b_y][x] == '0')
// 	{
// 		x--;
// 		iterator++;
// 	}
// 	if (iterator > r)
// 		r = iterator;
// 	iterator = 0;
// 	y = map_data->p_pos.b_y - 1;
// 	while (y >= 0 && map_data->map[y][map_data->p_pos.b_x] == '0')
// 	{
// 		y--;
// 		iterator++;
// 	}
// 	if (iterator > r)
// 		r = iterator;
// 	return (r);
// }

// int	trace_perimeter(t_map_data *map_data, int r, double alpha)
// {
// 	// double	h;
// 	// double	k;
// 	// double	radiant;
// 	// int		i;

// 	// i = 0;
// 	(void)r;
// 	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window,
// 		map_data->p_pos.r_x * WIDTH, map_data->p_pos.r_y * HEIGHT, 0XFF0000);
// 	// while (i < 5000)
// 	// {
// 	// 	radiant = 2 * M_PI * i / 5000;
// 	// 	h = map_data->p_pos.r_x + r * cos(radiant);
// 	// 	k = map_data->p_pos.r_y + r * sin(radiant);
// 	// 	mlx_pixel_put(map_data->mlx->init, map_data->mlx->window, h * WIDTH, k
// 	// 		* HEIGHT, 0XFFFFFF);
// 	// 	i++;
// 	// }
// 	raycast(map_data, find_r(map_data), define_fov(map_data, find_r(map_data),
// 			alpha), 1500);
// 	return (1);
// }

void	fill_ceiling(t_map_data *map, int x, int draw_start)
{
	int		y;
	char	*target;

	y = 0;
	while (y < draw_start)
	{
		target = map->mlx.img.adrr + (y * map->mlx.img.size_line + x
				* (map->mlx.img.bits_per_pixel / 8));
		*(unsigned int *)target = map->input.ceiling_color;
		y++;
	}
}

void	draw_wall_stripe(t_map_data *map, int x, int draw_start, int draw_end,
		double wall_x, int i)
{
	int		y;
	char	*target;
	char	*target_1;
	int		texture_x;
	int		texture_y;
	int		text_width;

	y = draw_start;
	text_width = 64;
	while (y <= draw_end)
	{
		texture_y = (y - draw_start) * map->mlx.wall[i].width / (draw_end
				- draw_start);
		texture_x = (int)(wall_x * text_width) % text_width;
		target = map->mlx.wall[i].adrr + (texture_y * map->mlx.wall[i].size_line
				+ texture_x * (map->mlx.wall[i].bits_per_pixel / 8));
		target_1 = map->mlx.img.adrr + (y * map->mlx.img.size_line + x
				* (map->mlx.img.bits_per_pixel / 8));
		*(unsigned int *)target_1 = *(unsigned int *)target;
		y++;
	}
}

void	draw_door_stripe(t_map_data *map, int x, int draw_start, int draw_end,
		double wall_x, int i)
{
	int		y;
	char	*target;
	char	*target_1;
	int		texture_x;
	int		texture_y;
	int		text_width;

	y = draw_start;
	text_width = 64;
	while (y <= draw_end)
	{
		texture_y = (y - draw_start) * map->mlx.door.width / (draw_end
				- draw_start);
		texture_x = (int)(wall_x * text_width) % text_width;
		target = map->mlx.door.adrr + (texture_y * map->mlx.door.size_line
				+ texture_x * (map->mlx.wall[i].bits_per_pixel / 8));
		target_1 = map->mlx.img.adrr + (y * map->mlx.img.size_line + x
				* (map->mlx.img.bits_per_pixel / 8));
		*(unsigned int *)target_1 = *(unsigned int *)target;
		y++;
	}
}

void	fill_floor(t_map_data *map, int x, int draw_end)
{
	int		y;
	char	*target;

	y = draw_end + 1;
	while (y <= map->mlx.height)
	{
		target = map->mlx.img.adrr + (y * map->mlx.img.size_line + x
				* (map->mlx.img.bits_per_pixel / 8));
		*(unsigned int *)target = map->input.floor_color;
		y++;
	}
}

void	print_stripe(t_map_data *map, int x, int draw_start, int draw_end,
		double wall_x, int i)
{
	fill_ceiling(map, x, draw_start);
	if (i == D)
		draw_door_stripe(map, x, draw_start, draw_end, wall_x, i);
	else
		draw_wall_stripe(map, x, draw_start, draw_end, wall_x, i);
	fill_floor(map, x, draw_end);
}

void	set_ray_variables(t_ray *ray, t_map_data *data)
{
	ray->hit = 0;
	ray->camerax = 2 * ray->x / (double)data->mlx.width - 1;
	ray->raydirx = data->p_pos.dir_x + data->p_pos.plane_x * ray->camerax;
	ray->raydiry = data->p_pos.dir_y + data->p_pos.plane_y * ray->camerax;
	ray->mapx = (int)data->p_pos.r_x;
	ray->mapy = (int)data->p_pos.r_y;
	ray->deltadistx = set_deltadist(ray->raydirx);
	ray->deltadisty = set_deltadist(ray->raydiry);
	ray->stepx = sign(ray->raydirx);
	ray->sidedistx = set_side_dist(ray->raydirx, data->p_pos.r_x, ray->mapx,
			ray->deltadistx);
	ray->stepy = sign(ray->raydiry);
	ray->sidedisty = set_side_dist(ray->raydiry, data->p_pos.r_y, ray->mapy,
			ray->deltadisty);
}

void	open_door_gesture(t_ray *ray, t_map_data *data)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
	if (data->map[ray->mapy][ray->mapx] == 'O' && ray->perpwalldist <= 2)
	{
		data->door_trigger = 1;
		data->door_x = ray->mapx;
		data->door_y = ray->mapy;
	}
}

void	dda(t_ray *ray, t_map_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (data->map[ray->mapy][ray->mapx] == 'O')
			open_door_gesture(ray, data);
		if (data->map[ray->mapy][ray->mapx] == '1'
			|| data->map[ray->mapy][ray->mapx] == 'D')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
	if (data->map[ray->mapy][ray->mapx] == 'D' && ray->perpwalldist <= 2)
	{
		data->door_trigger = 1;
		data->door_x = ray->mapx;
		data->door_y = ray->mapy;
	}
}

void	print_on_display(t_ray *ray, t_map_data *data, double wall_x)
{
	if (data->map[ray->mapy][ray->mapx] == 'D')
		print_stripe(data, ray->x, ray->draw_start, ray->draw_end, wall_x, D);
	else if (ray->side == 1 && ray->raydiry >= 0)
		print_stripe(data, ray->x, ray->draw_start, ray->draw_end, wall_x, S);
	else if (ray->side == 1 && ray->raydiry < 0)
		print_stripe(data, ray->x, ray->draw_start, ray->draw_end, wall_x, N);
	else if (ray->side == 0 && ray->raydirx >= 0)
		print_stripe(data, ray->x, ray->draw_start, ray->draw_end, wall_x, E);
	else if (ray->side == 0 && ray->raydirx < 0)
		print_stripe(data, ray->x, ray->draw_start, ray->draw_end, wall_x, W);
}

void	raycasting(t_map_data *data)
{
	t_ray	ray;
	int		wallheight;
	double	wall_x;

	ray.x = 0;
	while (ray.x < data->mlx.width)
	{
		set_ray_variables(&ray, data);
		dda(&ray, data);
		wallheight = (int)(data->mlx.height / ray.perpwalldist);
		ray.draw_start = -wallheight / 2 + data->mlx.height / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = wallheight / 2 + data->mlx.height / 2;
		if (ray.draw_end >= data->mlx.height)
			ray.draw_end = data->mlx.height - 1;
		if (ray.side == 0)
			wall_x = data->p_pos.r_y + ray.perpwalldist * ray.raydiry;
		else
			wall_x = data->p_pos.r_x + ray.perpwalldist * ray.raydirx;
		wall_x -= floor(wall_x);
		print_on_display(&ray, data, wall_x);
		ray.x++;
	}
}
