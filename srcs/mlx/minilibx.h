/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:15:47 by madamou           #+#    #+#             */
/*   Updated: 2024/09/13 18:21:03 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H
# define MINILIBX_H

# include <X11/keysym.h>

# define WIDTH 16
# define HEIGHT 16
# define WIDTH_X2 64
# define HEIGHT_X2 64
# define SENSITIVITY 0.02
# define MIN_MOUSE_MOVE 5
# define WHITE_I "assets/white_tile.xpm"
# define BLACK_I "assets/black_tile.xpm"
# define WALL "assets/wall_sprite.xpm"
# define COIN "assets/coin_sprite.xpm"
# define DOOR "assets/door_sprite.xpm"
# define ENEMY "assets/enemy.xpm"
# define DOT "assets/dot.xpm"
# define BLUE "assets/door_m_map.xpm"
# define GUN "assets/gun_sprite.xpm"
# define SHOOT_1 "assets/animations/shoot_anime1.xpm"
# define SHOOT_2 "assets/animations/shoot_anime2.xpm"
# include "../../includes/cube3D.h"

# ifdef CUBE3D_H
#  undef CUBE3D_H
# endif

// typedef struct s_map_data	t_map_data;

int		init_mlx(t_map_data *data);
void	destroy_mlx(t_map_data *data);

// player move

void	right(t_map_data *data, double move_speed);
void	left(t_map_data *data, double move_speed);
void	forward(t_map_data *data, double move_speed);
void	behind(t_map_data *data, double move_speed);

// fov move
//
void	right_fov(t_map_data *data, double old_dir_x, double rot_speed,
			double old_plane_x);
void	left_fov(t_map_data *data, double old_dir_x, double rot_speed,
			double old_plane_x);

// trigger functions
int		click_cross(t_map_data *data);
int		handle_input(int keysym, t_map_data *data);
int		render(t_map_data *data);
int		key_prees(int keysym, t_map_data *data);
int		key_release(int keysym, t_map_data *data);

// animations
void	animate_gun(t_map_data *data, int an);

#endif
