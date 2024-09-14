/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:54:14 by itahri            #+#    #+#             */
/*   Updated: 2024/09/14 08:37:18 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycatsing.h"
#include <X11/X.h>
#include <stdbool.h>
#include <stdio.h>

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

void	fill_ceiling(t_map_data *map, t_ray *ray)
{
	char	*target;

	while (ray->coord.y < ray->draw_start)
	{
		target = map->mlx.img.adrr + (ray->coord.y * map->mlx.img.size_line + ray->coord.x
				* (map->mlx.img.bits_per_pixel / 8));
		if (*(unsigned int *)target != (unsigned int)map->input.ceiling_color)
			*(unsigned int *)target = (unsigned int)map->input.ceiling_color;
		ray->coord.y++;
	}
}

void	draw_wall_stripe(t_map_data *map, t_ray *ray, int i)
{
	char	*texture_color;
	char	*screen_pixel;
	int		texture_x;
	int		texture_y;
	double step;
	double tex_pos;

	texture_x = (int)(ray->wall_x * map->mlx.wall[i].width);
	if ((ray->side == 0 && ray->ray_dir.x > 0)
		|| (ray->side == 1 && ray->ray_dir.y < 0))
		texture_x = map->mlx.wall[i].width - texture_x - 1;
	step = 1.0 * map->mlx.wall[i].height / ray->wallheight;
	tex_pos = (ray->draw_start - map->mlx.height / 2 + ray->wallheight / 2) * step;
	while (ray->coord.y <= ray->draw_end)
	{
		texture_y = (int)tex_pos % map->mlx.wall[i].height;
        tex_pos += step;
		texture_color = map->mlx.wall[i].adrr + (texture_y * map->mlx.wall[i].size_line
				+ texture_x * (map->mlx.wall[i].bits_per_pixel / 8));
		screen_pixel = map->mlx.img.adrr + (ray->coord.y * map->mlx.img.size_line + ray->coord.x
				* (map->mlx.img.bits_per_pixel / 8));
		if (*(unsigned int *)screen_pixel != *(unsigned int *)texture_color)
			*(unsigned int *)screen_pixel = *(unsigned int *)texture_color;
		ray->coord.y++;
	}
}

void	draw_door_stripe(t_map_data *map, t_ray *ray)
{
	char	*texture_color;
	char	*screen_pixel;
	int		texture_x;
	int		texture_y;
	double step;
	double tex_pos;

	texture_x = (int)(ray->wall_x * map->mlx.door.width);
	if ((ray->side == 0 && ray->ray_dir.x > 0)
		|| (ray->side == 1 && ray->ray_dir.y < 0))
		texture_x = map->mlx.door.width - texture_x - 1;
	step = 1.0 * map->mlx.door.height / ray->wallheight;
	tex_pos = (ray->draw_start - map->mlx.height / 2 + ray->wallheight / 2) * step;
	while (ray->coord.y <= ray->draw_end)
	{
		texture_y = (int)tex_pos % map->mlx.door.height;
        tex_pos += step;
		texture_color = map->mlx.door.adrr + (texture_y * map->mlx.door.size_line
				+ texture_x * (map->mlx.door.bits_per_pixel / 8));
		screen_pixel = map->mlx.img.adrr + (ray->coord.y * map->mlx.img.size_line + ray->coord.x
				* (map->mlx.img.bits_per_pixel / 8));
		if (*(unsigned int *)screen_pixel != *(unsigned int *)texture_color)
			*(unsigned int *)screen_pixel = *(unsigned int *)texture_color;
		ray->coord.y++;
	}
}

void	draw_enemies(t_map_data *map, t_ray *ray)
{
	char	*texture_color;
	char	*screen_pixel;
	int		texture_x;
	int		texture_y;
	double step;
	double tex_pos;
    char *test;

    test = "\0";
	texture_x = (int)(ray->wall_x * map->mlx.enemy.img.width);
	if ((ray->side == 0 && ray->ray_dir.x > 0)
		|| (ray->side == 1 && ray->ray_dir.y < 0))
		texture_x = map->mlx.enemy.img.width - texture_x - 1;
	step = 1.0 * map->mlx.enemy.img.height / ray->wallheight;
	tex_pos = (ray->draw_start - map->mlx.height / 2 + ray->wallheight / 2) * step;
	while (ray->coord.y <= ray->draw_end)
	{
		texture_y = (int)tex_pos % map->mlx.enemy.img.height;
        tex_pos += step;
		texture_color = map->mlx.enemy.img.adrr + (texture_y * map->mlx.enemy.img.size_line
				+ texture_x * (map->mlx.enemy.img.bits_per_pixel / 8));
		screen_pixel = map->mlx.img.adrr + (ray->coord.y * map->mlx.img.size_line + ray->coord.x
				* (map->mlx.img.bits_per_pixel / 8));
		if (*(unsigned int *)texture_color != 0xFF000000)
			*(unsigned int *)screen_pixel = *(unsigned int *)texture_color;
		ray->coord.y++;
	}
}

void	fill_floor(t_map_data *map, t_ray *ray)
{
	char	*target;

	while (ray->coord.y <= map->mlx.height)
	{
		target = map->mlx.img.adrr + (ray->coord.y * map->mlx.img.size_line + ray->coord.x
				* (map->mlx.img.bits_per_pixel / 8));
		if (*(unsigned int *)target != (unsigned int)map->input.floor_color)
			*(unsigned int *)target = (unsigned int)map->input.floor_color;
		ray->coord.y++;
	}
}

void	print_stripe(t_map_data *map, t_ray *ray, int i)
{
	fill_ceiling(map, ray);
	if (i == D)
		draw_door_stripe(map, ray);
	else if  (i == M)
		draw_enemies(map, ray);
	else
		draw_wall_stripe(map, ray, i);
	fill_floor(map, ray);
}

void set_ray_variables(t_ray *ray, t_map_data *data)
{
    ray->hit = 0;
    ray->coord.y = 0;
    ray->camera_x = 2 * ray->coord.x / (double)data->mlx.width - 1;
    ray->ray_dir.x = data->p_pos.dir_x + data->p_pos.plane_x * ray->camera_x;
    ray->ray_dir.y = data->p_pos.dir_y + data->p_pos.plane_y * ray->camera_x;
    ray->map.x = (int)data->p_pos.r_x;
    ray->map.y = (int)data->p_pos.r_y;
    ray->delta_dist.x = set_deltadist(ray->ray_dir.x);
    ray->delta_dist.y = set_deltadist(ray->ray_dir.y);
    ray->step.x = sign(ray->ray_dir.x);
    ray->side_dist.x = set_side_dist(ray->ray_dir.x, data->p_pos.r_x, ray->map.x, ray->delta_dist.x);
    ray->step.y = sign(ray->ray_dir.y);
    ray->side_dist.y = set_side_dist(ray->ray_dir.y, data->p_pos.r_y, ray->map.y, ray->delta_dist.y);
}

void open_door_gesture(t_ray *ray, t_map_data *data)
{
    if (ray->side == 0)
        ray->perpwalldist = (ray->side_dist.x - ray->delta_dist.x);
    else
        ray->perpwalldist = (ray->side_dist.y - ray->delta_dist.y);
    
    if (data->map[ray->map.y][ray->map.x] == 'O' && ray->perpwalldist <= 2)
    {
        data->door_trigger = 1;
        data->door_x = ray->map.x;
        data->door_y = ray->map.y;
    }
}

void dda(t_ray *ray, t_map_data *data)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map.x += ray->step.x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map.y += ray->step.y;
            ray->side = 1;
        }

        if (data->map[ray->map.y][ray->map.x] == 'O')
            open_door_gesture(ray, data);
        if (data->map[ray->map.y][ray->map.x] == '1'
			|| data->map[ray->map.y][ray->map.x] == 'D'
            || data->map[ray->map.y][ray->map.x] == 'M')
            ray->hit = 1;
    }
    if (ray->side == 0)
        ray->perpwalldist = (ray->side_dist.x - ray->delta_dist.x);
    else
        ray->perpwalldist = (ray->side_dist.y - ray->delta_dist.y);
    if (data->map[ray->map.y][ray->map.x] == 'D' && ray->perpwalldist <= 2)
    {
        data->door_trigger = 1;
        data->door_x = ray->map.x;
        data->door_y = ray->map.y;
    }
}

int dda_enemies(t_ray *ray, t_map_data *data)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->delta_dist.x;
            ray->map.x += ray->step.x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->delta_dist.y;
            ray->map.y += ray->step.y;
            ray->side = 1;
        }
        if (data->map[ray->map.y][ray->map.x] == '1'
			|| data->map[ray->map.y][ray->map.x] == 'D')
            return (0);
        if (data->map[ray->map.y][ray->map.x] == 'M')
            ray->hit = 1;
    }
    if (ray->side == 0)
        ray->perpwalldist = (ray->side_dist.x - ray->delta_dist.x);
    else
        ray->perpwalldist = (ray->side_dist.y - ray->delta_dist.y);
    return (1);
}


void print_on_display(t_ray *ray, t_map_data *data)
{
    if (data->map[ray->map.y][ray->map.x] == 'D')
        print_stripe(data, ray,  D);
    else if (data->map[ray->map.y][ray->map.x] == 'M')
        print_stripe(data, ray,  M);
    else if (ray->side == 1 && ray->ray_dir.y >= 0)
        print_stripe(data, ray, S);
    else if (ray->side == 1 && ray->ray_dir.y < 0)
        print_stripe(data, ray, N);
    else if (ray->side == 0 && ray->ray_dir.x >= 0)
        print_stripe(data, ray, E);
    else if (ray->side == 0 && ray->ray_dir.x < 0)
        print_stripe(data, ray, W);
}

void raycasting(t_map_data *data)
{
    t_ray   ray;

    ray.coord.x = 0;
    while (ray.coord.x < data->mlx.width)
    {
        set_ray_variables(&ray, data);
        dda(&ray, data);
        ray.wallheight = (int)(data->mlx.height / ray.perpwalldist);
        ray.draw_start = -ray.wallheight / 2 + data->mlx.height / 2;
        if (ray.draw_start < 0)
            ray.draw_start = 0;
        ray.draw_end = ray.wallheight / 2 + data->mlx.height / 2;
        if (ray.draw_end >= data->mlx.height)
            ray.draw_end = data->mlx.height - 1;
        
        if (ray.side == 0)
            ray.wall_x = data->p_pos.r_y + ray.perpwalldist * ray.ray_dir.y;
        else
            ray.wall_x = data->p_pos.r_x + ray.perpwalldist * ray.ray_dir.x;
        
        ray.wall_x -= floor(ray.wall_x);
        print_on_display(&ray, data);
        ray.coord.x++;
    }
    ray.coord.x = 0;
    while (ray.coord.x < data->mlx.width)
    {
        set_ray_variables(&ray, data);
        if (dda_enemies(&ray, data) == 0)
        {
            ray.coord.x++;
            continue;
        }
        ray.wallheight = (int)(data->mlx.height / ray.perpwalldist);
        ray.draw_start = -ray.wallheight / 2 + data->mlx.height / 2;
        if (ray.draw_start < 0)
            ray.draw_start = 0;
        ray.draw_end = ray.wallheight / 2 + data->mlx.height / 2;
        if (ray.draw_end >= data->mlx.height)
            ray.draw_end = data->mlx.height - 1;
        
        if (ray.side == 0)
            ray.wall_x = data->p_pos.r_y + ray.perpwalldist * ray.ray_dir.y;
        else
            ray.wall_x = data->p_pos.r_x + ray.perpwalldist * ray.ray_dir.x;
        
        ray.wall_x -= floor(ray.wall_x);
        print_on_display(&ray, data);
        ray.coord.x++;
    }
}

