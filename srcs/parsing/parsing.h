/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:04:46 by itahri            #+#    #+#             */
/*   Updated: 2024/10/01 16:14:37 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define NO 20
# define SO 21
# define EA 22
# define WE 23
# define F 24
# define C 25

# ifdef CUBE3D_H
#  undef CUBE3D_H
# endif

/*
 * 0 = floor
 * 1 = wall
 * (N-S-E-W) = player spawn point and cardinal direction
 */

/*
 * b_x & b_y = x and y pos in orhtogonal buffer

	* r_x & r_y = x and y pos in mlx render when r_x = 2.0 b_x = 2
  * but when r_x = 1.9 b_x still egal to 1
 */

typedef struct s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct s_coord
{
	double			r_x;
	double			r_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				mouse_x;
	int				mouse_y;
	t_vec			direction;
	double			dir_length;
}					t_coord;

typedef struct s_img
{
	void			*img;
	char			*path;
	char			*adrr;
	int				size_line;
	int				bits_per_pixel;
	int				bits_per_pixel_div8;
	int				endiant;
	int				width;
	int				height;
}					t_img;

typedef struct s_input
{
	char			*tx_north;
	char			*tx_south;
	char			*tx_east;
	char			*tx_west;
	char			*tx_floor;
	int				floor_color;
	char			*tx_ceiling;
	int				ceiling_color;
}					t_input;

# define N 0
# define S 1
# define E 2
# define W 3
# define D 4
# define M 5

typedef struct s_enemies
{
	t_img			img;
	unsigned int	spawn;
}					t_enemies;

typedef struct s_mlx
{
	int				width;
	int				height;
	int				width_div2;
	int				height_div2;
	void			*init;
	void			*window;
	t_img			img;
	t_img			wall[4];
	t_img			door;
	t_img			white;
	t_enemies		enemy;
	t_img			dot;
	t_img			blue;
	t_img			gun;
	t_img			shoot[2];
	t_img			crosshair;
}					t_mlx;

typedef struct s_key
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				cam_left;
	int				cam_right;
	int				escape;
	int				space;
	float			speed_boost;
	int				fire;
	int				del_sprite;
	int				mouse_hide;
}					t_key;

typedef enum s_sprite_type
{
	MONSTER,
}					t_sprite_type;

typedef struct s_sprite
{
	t_sprite_type	type;
	t_vec			pos;
	struct s_sprite	*next;
}					t_sprite;

typedef struct s_map_data
{
	t_input			input;
	t_mlx			mlx;
	t_coord			p_pos;
	int				door_trigger;
	int				door_x;
	int				door_y;
	char			**map;
	t_key			key;
	double			delta_time;
	t_sprite		*sprites;
	int				nb_sprites;
}					t_map_data;

// parsing
t_map_data			*get_map_data(char *filename, t_map_data *data);

// map_parsing
int					get_map(t_map_data *map_data, char *line, int fd);

// utils
int					ft_isspace(char c);
int					check_type(char *line);
void				assign_path(char *path, t_map_data *map_data, int type);
int					get_path(char *line, t_map_data *map_data, int type);
void				parse_line(char *line, int fd, t_map_data *map_data);

// checking
int					check_map(t_map_data *data);
int					check_map_playable(t_map_data *data);

#endif
