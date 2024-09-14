/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 12:56:24 by itahri            #+#    #+#             */
/*   Updated: 2024/09/08 17:27:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# ifdef CUBE3D_H
#  undef CUBE3D_H
# endif

# include "../../includes/cube3D.h"

// typedef struct s_map_data	t_map_data;
# define M_PI 3.14159265358979323846 /* pi */
# define PRECISION 50

typedef struct s_ray
{
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		side;
	int		hit;
	double	raydirx;
	double	raydiry;
	double	camerax;
	int		x;
	int		draw_start;
	int		draw_end;
}			t_ray;

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
