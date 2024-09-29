/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:15:47 by madamou           #+#    #+#             */
/*   Updated: 2024/09/29 06:08:28 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINILIBX_H
# define MINILIBX_H

# include <X11/X.h>
# include <X11/keysym.h>

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
# define GUN "assets/animations/gun_2.xpm"
# define SHOOT_1 "assets/animations/shoot_anime1.xpm"
# define SHOOT_2 "assets/animations/shoot_anime2.xpm"
# include "../../includes/cube3D.h"

# ifdef CUBE3D_H
#  undef CUBE3D_H
# endif

typedef struct s_vec	t_vec;
typedef struct s_vecint	t_vecint;
// typedef struct s_map_data	t_map_data;

int		init_mlx(t_map_data *data);
void	destroy_mlx(t_map_data *data);
void	new_image(t_map_data *data, t_img *img);
void	path_to_mlx_img(t_map_data *data, t_mlx *mlx);
void	ft_init_img(t_map_data *data, t_img *img);

// player move

void	right(t_map_data *data, double move_speed);
void	left(t_map_data *data, double move_speed);
void	forward(t_map_data *data, double move_speed);
void	behind(t_map_data *data, double move_speed);
void	handle_player_movement(t_map_data *data);
void	handle_door_interaction(t_map_data *data, bool *is_press);

// fov move
//
void	right_fov(t_map_data *data, double rot_speed);
void	left_fov(t_map_data *data, double rot_speed);
void	handle_camera_movement(t_map_data *data);

// trigger functions
int		mouse_click(int button, int x, int y, t_map_data *data);
int		click_cross(t_map_data *data);
int		handle_input(int keysym, t_map_data *data);
int		render(t_map_data *data);
int		key_prees(int keysym, t_map_data *data);
int		key_release(int keysym, t_map_data *data);
void	mouse_movement(t_map_data *data);

// display
void	display_gun(t_map_data *data, t_img img_sprite);
void	display_crosshair(t_map_data *data);
void	handle_gun_fire(t_map_data *data, int *cnt);
void	change_player(t_map_data *data);

// draw
void	draw_single_pixel(t_map_data *data, int x, int y, char *gun_color);
void	draw_scaled_pixel(t_map_data *data, t_vecint img, t_vecint gun,
			t_img *img_sprite);

// animations
void	animate_gun(t_map_data *data, int *an);

#endif
