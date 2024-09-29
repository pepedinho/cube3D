/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:56:24 by itahri            #+#    #+#             */
/*   Updated: 2024/09/29 05:02:28 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# ifndef CUBE3D
#  include "../../includes/cube3D.h"
# endif
// typedef struct s_map_data	t_map_data;

# define M_PI 3.14159265358979323846 /* pi */
# define PRECISION 50
# define RAD_TO_DEG (180.0 / M_PI)

typedef struct s_vecint
{
	int			x;
	int			y;
}				t_vecint;

typedef struct s_ray
{
	t_vec		side_dist;
	t_vec		delta_dist;
	t_vec		cam_s;
	t_vec		cam_e;
	double		perpwalldist;
	t_vecint	map;
	t_vecint	step;
	int			side;
	int			hit;
	t_vec		ray_dir;
	double		camera_x;
	t_vecint	coord;
	int			draw_start;
	int			draw_end;
	int			wallheight;
	double		wall_x;
	double		z_buffer[1920];
}				t_ray;

typedef struct s_render_sprite
{
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	t_vecint	draw_start;
	t_vecint	draw_end;
	int			d;
	char		*texture_color;
	char		*screen_pixel;
	int			x;
	int			y;
	t_vec		transform;
}t_render_sprite;

// Draw stripe
void	print_stripe(t_map_data *map, t_ray *ray, int i);
void	fill_floor(t_map_data *map);
void	fill_ceiling(t_map_data *map);


// raycast
int				trace_perimeter(t_map_data *map_data, int r);
int				find_r(t_map_data *map_data);
double			abs_value(double nb);
void	open_door_gesture(t_ray *ray, t_map_data *data);
void	dda(t_ray *ray, t_map_data *data);

// raycast_sprite
t_vec set_current_sprite_position(t_map_data *data, int index);
t_vec set_transform(t_map_data *data, t_vec sprite);
void sprite_render(t_map_data *data, t_render_sprite *render_s, t_ray *ray);
void set_sprite_data(t_map_data *data, int index, t_render_sprite *render_s);
int *order_sprite_with_distance(t_map_data *data);


// utils
int				encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int				sign(double nb);
double			set_side_dist(double ray_dir, double pos, int map,
					double delta);
double			set_deltadist(double raydir);

// mini map
void			render_map(t_map_data *map_data);
void			raycasting(t_map_data *data);

// enemy
int				check_if_crosshair_on_enemy(t_map_data *data);

#endif
