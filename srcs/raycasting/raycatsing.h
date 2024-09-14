/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:56:24 by itahri            #+#    #+#             */
/*   Updated: 2024/09/14 08:41:08 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

#ifndef CUBE3D
# include "../../includes/cube3D.h"
#endif
// typedef struct s_map_data	t_map_data;

# define M_PI		3.14159265358979323846	/* pi */
# define PRECISION 50

typedef struct s_vec
{
	double x;
	double y;
}t_vec;

typedef struct s_vecint
{
	int x;
	int y;
}t_vecint;

typedef struct s_ray
{
	t_vec side_dist;
	t_vec delta_dist;
	double perpwalldist;
	t_vecint map;
	t_vecint step;
	int side;
	int hit;
	t_vec ray_dir;
	double camera_x;
	t_vecint coord;
	int draw_start;
	int draw_end;
	int     wallheight;
    double  wall_x;
} t_ray;


// raycast
int			trace_perimeter(t_map_data *map_data, int r);
int			find_r(t_map_data *map_data);
double		abs_value(double nb);

// utils
int			encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int			sign(double nb);
double		set_side_dist(double ray_dir, double pos, int map, double delta);
double		set_deltadist(double raydir);

// mini map
void		render_map(t_map_data *map_data);
void		raycasting(t_map_data *data);

#endif
